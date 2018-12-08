#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
    iterator = NULL;
}

LinkedList::~LinkedList()
{
    free();
}

void LinkedList::addNode(std::string str)
{
    node* new_node = new node;
    new_node->text = str;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
        tail = new_node;
        iterator = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = tail->next;
    }
}

bool LinkedList::next()
{
    if (iterator->next != NULL)
    {
        iterator = iterator->next;
        return true;
    }

    return false;
}

std::string LinkedList::getCurrent()
{
    return iterator->text;
}

void LinkedList::free()
{
    // untested
    node* tmp = head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}