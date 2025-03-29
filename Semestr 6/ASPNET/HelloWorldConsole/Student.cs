namespace HelloWorld
{

    internal class Student : Person
    {
        public string StudentID { get; set; }

        public Student(string studentId, string name, string surname, int yob_) : base(name, surname, yob_)
        {
            StudentID = studentId;
        }

        public override string ToString()
        {
            return base.ToString() + StudentID;
        }
    }
}