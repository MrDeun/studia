#include <cstddef>
#include <iostream>
template<class data_type>
class queue_list{
    private:
        class node{
            public:
            data_type data;
            node* next = nullptr;
            node(data_type new_data): data(new_data){}
            ~node(){}
        };
        node* head = nullptr;
        size_t size = 0;
    public:
        queue_list(){}
        queue_list(data_type data_in){
            head = new node(data_in);
            size++;
        }
        ~queue_list(){
            while(pop_front()){}
            delete head;
        }
        void append(data_type new_data){
            node* current_node = head;
            while (current_node->next != nullptr){
                current_node = current_node->next;
            }
            current_node->next = new node(new_data);
            size++;
        }

        bool pop_front(){
            if(head->next == nullptr)
                return false;
            node* temp = head->next;
            delete head;
            head = temp;
            temp = nullptr;
            delete temp;
            size--;
            return true;
        }

        data_type& find(size_t index){
            if (size < index){
                throw "ERROR: TRIED TO ACCESS ELEMENT OUTSIDE OF STRUCTURE!";
            }
            
            node* current_node = head;
            for (size_t i = 0; i <= index; i++){
                if (i == index) {
                    return current_node->data;
                } else {
                    current_node = current_node->next;
                }
            }  
        }
};

int main(){
    queue_list<int> hello_list;
    hello_list.append(6);
    hello_list.append(8);
    std::cout << hello_list.find(0) << ' ' << hello_list.find(1);
    hello_list.pop_front();
    return 0;
}