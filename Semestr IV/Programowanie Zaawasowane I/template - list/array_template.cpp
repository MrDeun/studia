    #include <iostream>
    template<class Type>
    class array{
        private:
            Type* _ptr;
            size_t _size;
            bool check_index(size_t index){
                return (index<_size);
            }
        public:
            array(size_t size_in): _size(size_in),_ptr(new Type[size_in]) {}
            ~array() {
                delete[] _ptr;
            }

            array(const array& arr){
                _size = arr.size();
                _ptr = new Type[_size];
                for (size_t i = 0; i < _size; i++) {
                   _ptr[i] = arr[i];
                }
            }

            void insert(Type value, size_t index){
                if (check_index(index)){
                    _ptr[index] = value;
                    return;
                } else {
                    std::cerr << "Damn it Bobby, you tried to put value outside of array!\n";
                    std::terminate();
                }
            }

            Type& operator[](size_t index){
                if(check_index(index)){
                    return _ptr[index];
                } else{
                    std::cerr << "Damn it Bobby, you tried to access value outside of array!\n";
                    std::terminate();
                }
            }

            void operator=(const array& sub){
                delete[] ptr;
                _size = sub.size();
                _ptr = sub.ptr();
            }

            size_t size(){
                return _size;
            }

            Type* ptr(){
                return _ptr;
            }

            void print(){
                for (int i = 0; i < _size; i++){
                    std::cout << _ptr[i] << " "; 
                }
            }
    };

    int main(){
        array<int> safe_array{6};
        for (int i = 0; i < safe_array.size(); i++){
            safe_array[i] = i+1;
        }

        safe_array.print();
        std::cout << safe_array[6];
        return 0;
    }