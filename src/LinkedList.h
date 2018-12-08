#include <string>

struct node
{
    std::string text;
    node* next;
};

class LinkedList
{
    public:
        LinkedList();
        ~LinkedList();
        void addNode(std::string str);
        void free();
        bool next();
        std::string getCurrent();

    private:
        node* head;
        node* tail;
        node* iterator;
};