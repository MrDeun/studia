#include<iostream>

class Vehicle
{
    private:
        int WheelCount;
    protected:
        std::string VehicleID;
        std::string Color;
    public:
        std::string ExparationDate;
        Vehicle(int WheelCount_in,std::string Color_in, std::string VehicleID_in)
        {
            WheelCount=WheelCount_in;
            VehicleID=VehicleID_in;
            Color=Color_in;
            std::cout<<"Vehicle has been created"<<std::endl;
        }
        ~Vehicle()
        {
            std::cout<<"Vehicle has been destroyed"<<std::endl;
        }

        void Start()
        {
            std::cout<<"I can't start!"<<std::endl;
            return;
        }
        void Go()
        {
            std::cout<<"I can't go!"<<std::endl;
            return;
        }
        void Stop()
        {
            std::cout<<"I can't stop!"<<std::endl;
            return;
        }

        void virtual Travel()
        {
            Start();Go();Stop();
            return;
        }

        void SetWheelCount(int WheelCount_in)
        {
            WheelCount=WheelCount_in;
            return;
        }

        void Describe()
        {
            std::cout<<"Wheel Count: "<<WheelCount
            <<" Vehicle's ID: "<<VehicleID
            <<" Color: "<<Color
            <<" Expiration Date: "<<ExparationDate
            <<std::endl;
        }

};

class Truck : public Vehicle
{
    public:
        bool doesTrailerExist;
        Truck(std::string Color_in, std::string VehicleID_in):Vehicle(12, Color_in, VehicleID_in)
        {
            std::cout<<"A truck has been created!"<<std::endl;
        }
        ~Truck()
        {
            std::cout<<"A truch has fallen from the road!"<<std::endl;
        }

        void Start()
        {
            std::cout<<"BZIUUUUUUM"<<std::endl;
            return;
        }
        void Go()
        {
            std::cout<<"WRUUUUUUM!"<<std::endl;
            return;
        }
        void Stop()
        {
            std::cout<<"PISSSSSSK (BUUM)!"<<std::endl;
            return;
        }

        void Describe()
        {
            Vehicle::Describe();
            if(doesTrailerExist)
                std::cout<<"Trailer Attached"<<std::endl;
            else
                std::cout<<"No trailer attached to the vehicle"<<std::endl;
        }
};

class Personal : public Vehicle
{
        public:
        bool doesHookExist;
        Personal(std::string Color_in, std::string VehicleID_in):Vehicle(4, Color_in, VehicleID_in)
        {
            std::cout<<"A personal car has been created!"<<std::endl;
        }
        ~Personal()
        {
            std::cout<<"A personal car has fallen from the road!"<<std::endl;
        }

        void Start()
        {
            std::cout<<"bziu"<<std::endl;
            return;
        }
        void Go()
        {
            std::cout<<"wrum!"<<std::endl;
            return;
        }
        void Stop()
        {
            std::cout<<"pisk (stuk)!"<<std::endl;
            return;
        }

        void Describe()
        {
            Vehicle::Describe();
            if(doesHookExist)
                std::cout<<"Hook exists!"<<std::endl;
            else
                std::cout<<"There are no hooks on this vehicle!"<<std::endl;
        }
};


void Travel(Vehicle* Vehicle_in)
{
    Vehicle_in->Start();Vehicle_in->Go();Vehicle_in->Stop();return;
}

int main()
{
    Vehicle* IVECO = new Vehicle(6,"White","ELA W6KM");
    Personal* SKODA = new Personal("Red","RKR 26JQ");

    SKODA->doesHookExist=false;

    IVECO->Describe();
    SKODA->Describe();
    
    
    IVECO->Travel();
    SKODA->Travel();

    Travel(IVECO);Travel(SKODA);
    delete IVECO;delete SKODA;

    return 0;
}