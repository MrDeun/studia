import matplotlib.pyplot as matp
import pandas as panda

name_dataset = panda.read_csv("./nazwiska.csv")
name_dataset = name_dataset.astype({'COUNT': 'int64','NAME':'str'})

name_dataset['bin'] = range(len(name_dataset))
scale = 0.01

# Plot histogram using matp.hist
matp.hist(name_dataset['bin'], bins=len(name_dataset), edgecolor='black', weights=name_dataset['COUNT'] * scale)
matp.xlabel('IMIĘ PIERWSZE')
matp.ylabel('LICZBA WYSTĄPIEŃ')
matp.title('Histogram for IMIĘ PIERWSZE')
matp.xticks(name_dataset['bin'], name_dataset['NAME'])
matp.show()