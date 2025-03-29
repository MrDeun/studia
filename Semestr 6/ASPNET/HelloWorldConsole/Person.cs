namespace HelloWorld {

    internal class Person {
        private string firstName;
        public string LastName { get; private set; }
        public int yearOfBirth;

        public Person(string name, string lastName, int yoB) {
            this.firstName = name;
            this.LastName = lastName;
            this.yearOfBirth = yoB;
        }

        public override bool Equals(object? obj)
        {
            if (obj is not Person) return false;
            Person p1 = (Person)obj;
            if (p1 == null) return false; 
            if (p1 == this) return true; 
            return p1.GetFirstName().Equals(firstName) && p1.LastName.Equals(LastName) && p1.yearOfBirth == yearOfBirth;
        }

        public override string ToString()
        {
            return firstName + " " + LastName;
        }

        public string GetFirstName() {
            return firstName;
        }
    }
}