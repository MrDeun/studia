using BankAccountNS;

namespace TestProject1;

[TestClass]
public sealed class TestMath
{
    private void TestSquareRootValue(double value)
    {
        double expected = value;
        double input = expected * expected;
        double actual = M_Math.squareRoot(input);
        
        Assert.AreEqual(expected,actual);
    }
    
    [TestMethod]
    public void TestSquareRootSingular()
    {
        double expected = 3.0;
        double input = expected * expected;
        
        double actual = M_Math.squareRoot(input);
        
        Assert.AreEqual(expected, actual,0.001,"Square root not equal");
    }

    [TestMethod]
    public void TestSquareRootRange()
    {
        for (double expected = 1e-8; expected <= 1e-8; expected *= 3.2)
        {
            TestSquareRootValue(expected);
        }
    }
    
}