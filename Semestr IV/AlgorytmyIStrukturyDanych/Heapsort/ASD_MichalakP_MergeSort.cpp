class Node
{
    public:
        Node(int value_in){value = value_in;}
        ~Node(){}

        int value;
        int childern = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        bool insert(int new_value)
        {
            if(left == nullptr)
            {
                left = new Node(new_value);
                childern++;
                return true;
            }
            else if(right == nullptr)
            {
                right = new Node(new_value);
                childern++;
                return true;
            }
            else
            {
                if (left->childern <= right->childern)
                {
                    if(!left->insert(new_value))
                        return false;
                    else
                    {
                        childern++;
                        return true;
                    }
                }
                else
                {
                    if(!left->insert(new_value))
                        return false;
                    else
                    {
                        childern++;
                        return true;
                    }
                }
                
            }
        }



};

class BinaryTree{
    private:
        Node root;
    public:
        BinaryTree(int head_value)
        {
            root.value = head_value;
            root.left = nullptr;
            root.right = nullptr;
        }

        void insert(int new_value)
        {
            if(!root.insert(new_value))
            {

            }
        }


};