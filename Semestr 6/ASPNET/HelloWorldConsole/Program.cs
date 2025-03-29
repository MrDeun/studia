// See https://aka.ms/new-console-template for more information
namespace HelloWorld{
    internal class Program{
        static void Main(string[] args){
            Console.WriteLine("Hello, World!");
            Person p = new Person("Jane", "Doe", 1956);
            Person p1 = new Person("Jane", "Dah", 1956);
            Student s = new Student("589152", "Jane", "Wierzchowski", 1988);

            List<Person> persons = new List<Person>();
            persons.Count();
            persons.Add(p);
            persons.Add(p1);
            persons.Add(s);
            foreach (var pp in persons)
            {
                Console.WriteLine(pp.LastName);
            }
        }
    };
}