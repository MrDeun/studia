import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.transforms as transforms
from torchvision.models import resnet34
import cv2
import numpy as np

class DoubleConv(nn.Module):
    def __init__(self, in_channels, out_channels):
        super().__init__()
        self.double_conv = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, kernel_size=3, padding=1),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True),
            nn.Conv2d(out_channels, out_channels, kernel_size=3, padding=1),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True)
        )

    def forward(self, x):
        return self.double_conv(x)

class UNet(nn.Module):
    def __init__(self):
        super().__init__()
        # Use pre-trained ResNet34 as encoder
        resnet = resnet34(pretrained=True)
        
        # Encoder (downsampling)
        self.encoder1 = nn.Sequential(resnet.conv1, resnet.bn1, resnet.relu)
        self.encoder2 = nn.Sequential(resnet.maxpool, resnet.layer1)
        self.encoder3 = resnet.layer2
        self.encoder4 = resnet.layer3
        self.encoder5 = resnet.layer4

        # Decoder (upsampling)
        self.decoder0 = DoubleConv(768,512)
        self.decoder1 = DoubleConv(512, 256)
        self.decoder2 = DoubleConv(256, 128)
        self.decoder3 = DoubleConv(128, 64)
        self.decoder4 = DoubleConv(64, 32)

        # Final segmentation layer
        self.final_conv = nn.Conv2d(32, 1, kernel_size=1)

    def forward(self, x):
        # Encoder
        e1 = self.encoder1(x)
        e2 = self.encoder2(e1)
        e3 = self.encoder3(e2)
        e4 = self.encoder4(e3)
        e5 = self.encoder5(e4)

        # Decoder with skip connections
        d1 = F.interpolate(e5, scale_factor=2, mode='bilinear', align_corners=True)
        d1 = torch.cat([d1, e4], dim=1)
        d1 = self.decoder1(d1)

        d2 = F.interpolate(d1, scale_factor=2, mode='bilinear', align_corners=True)
        d2 = torch.cat([d2, e3], dim=1)
        d2 = self.decoder2(d2)

        d3 = F.interpolate(d2, scale_factor=2, mode='bilinear', align_corners=True)
        d3 = torch.cat([d3, e2], dim=1)
        d3 = self.decoder3(d3)

        d4 = F.interpolate(d3, scale_factor=2, mode='bilinear', align_corners=True)
        d4 = torch.cat([d4, e1], dim=1)
        d4 = self.decoder4(d4)

        # Final segmentation output
        return torch.sigmoid(self.final_conv(d4))

def remove_background(model, image_path, threshold=0.5):
    # Load and preprocess image
    image = cv2.imread(image_path)
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Resize((256, 256)),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], 
                              std=[0.229, 0.224, 0.225])
    ])
    
    input_tensor = transform(image_rgb).unsqueeze(0)
    print(input_tensor.shape)

    output = model(input_tensor)
    # Predict mask
    with torch.no_grad():
        mask = model(input_tensor)[0][0]
    
    # Create binary mask
    binary_mask = (mask > threshold).float()
    
    # Convert mask to OpenCV format
    mask_np = binary_mask.numpy()
    mask_cv = (mask_np * 255).astype(np.uint8)
    mask_cv = cv2.resize(mask_cv, (image.shape[1], image.shape[0]))
    
    return mask_cv

def apply_mask_to_image(original_image, mask):
    # Create 4-channel image with transparency
    b, g, r = cv2.split(original_image)
    alpha = mask
    rgba_image = cv2.merge((b, g, r, alpha))
    
    return rgba_image

# Usage example
model = UNet()
# Load pre-trained weights here if available
input_image = 'heihachi.png'
mask = remove_background(model, input_image)
result = apply_mask_to_image(cv2.imread(input_image), mask)
cv2.imwrite('output_transparent.png', result)