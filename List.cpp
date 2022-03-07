#include "List.h"
List::List()//конструктор
{
	Size = 0;
	Low_size = 0;
	Medium_size = 0;
	High_size = 0;
	head = nullptr;
	rear_high = nullptr;
	rear_medium = nullptr;
	rear_low = nullptr;
}

List::~List()//деструктор
{
	clear();
}

List::List(const List& p)//констуктор копирования
{
	List::Node* node = p.head;
	while (node != nullptr) {
		this->push_back(node->data, node->pr);
		node = node->pNext;
	}
}

List::List(List&& p)//конструктор перемещения
{
	this->head = p.head;
	this->rear_low = p.rear_low;
	this->rear_medium = p.rear_medium;
	this->rear_high = p.rear_high;
	p.head = nullptr;
	p.rear_high = nullptr;
	p.rear_low = nullptr;
	p.rear_medium = nullptr;
	this->Size = p.Size;
	p.Size = 0;
	this->Low_size = p.Low_size;
	p.Low_size = 0;
	this->Medium_size = p.Medium_size;
	p.Medium_size = 0;
	this->High_size = p.High_size;
	p.High_size = 0;
}

List& List::operator=(const List& p)//копирующий оператор присваивания
{
	if (this == &p) {
		return *this;
	}
	this->clear();
	List::Node* node = p.head;
	while (node != nullptr) {
		this->push_back(node->data, node->pr);
		node = node->pNext;
	}
	return *this;
}

List& List::operator=(List&& p)//перемещающий оператор присваивания
{
	if (this == &p) {
		return *this;
	}
	this->clear();
	this->head = p.head;
	this->Low_size = p.Low_size;
	this->Medium_size = p.Medium_size;
	this->High_size = p.High_size;
	p.head = nullptr;
	p.rear_high = nullptr;
	p.rear_low = nullptr;
	p.rear_medium = nullptr;
	this->Size = p.Size;
	p.Size = 0;
	this->Low_size = p.Low_size;
	p.Low_size = 0;
	this->Medium_size = p.Medium_size;
	p.Medium_size = 0;
	this->High_size = p.High_size;
	p.High_size = 0;
	return *this;
}

void List::pop_front()//удаление первого элемента, изменение Head
{
	if (head == rear_high) {
		rear_high = nullptr;
	}
	else if (head == rear_medium) {
		rear_medium = nullptr;
	}
	else if (head == rear_low) {
		rear_low = nullptr;
	}
	if (head->pr == priority::high) {
		High_size--;
	}
	else if (head->pr == priority::medium) {
		Medium_size--;
	}
	else {
		Low_size--;
	}
	Node* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

void List::push_back(int data)//добавление в конец очереди элемента без приоритета(автоматически дается третий приоритет и ставится в конец)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
	else
	{
		Node* current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(data);
	}
	Low_size++;
	Size++;
}

void List::push_back(int data, priority pr)//добавление элемента с приоритетом
{
	if (head == nullptr)
	{
		head = new Node(data, pr);
		if (pr == priority::high) {
			rear_high = this->head;
			High_size++;
		}
		else if (pr == priority::medium) {
			rear_medium = this->head;
			Medium_size++;
		}
		else if (pr == priority::low) {
			rear_low = this->head;
			Low_size++;
		}
	}
	else if (pr == priority::high) {
		if (head->pr != priority::high) {
			head = new Node(data, pr, head);
			rear_high = head;
		}
		else {
			rear_high->pNext = new Node(data, pr, rear_high->pNext);
			rear_high = rear_high->pNext;
		}
		High_size++;
	}
	else if (pr == priority::medium) {
		if (head->pr == priority::low || head == nullptr) {
			head = new Node(data, pr, head);
			rear_medium = head;
		}
		else if (rear_medium == nullptr) {
			rear_high->pNext = new Node(data, pr, rear_high->pNext);
			rear_medium = rear_high->pNext;
		}
		else {
			rear_medium->pNext = new Node(data, pr, rear_medium->pNext);
			rear_medium = rear_medium->pNext;
		}
		Medium_size++;
	}
	else {
		if (rear_low != nullptr) {
			rear_low->pNext = new Node(data, pr);
			rear_low = rear_low->pNext;
			Low_size++;
		}
		else if (rear_medium != nullptr) {
			rear_medium->pNext = new Node(data, pr);
			rear_low = rear_medium->pNext;
			Low_size++;
		}
		else {
			rear_high->pNext = new Node(data, pr);
			rear_low = rear_high->pNext;
			Low_size++;
		}
	}
	Size++;
}

void List::clear()//очищение
{
	while (Size)
	{
		pop_front();
	}
}

int List::GetSize()const {
	return Size;
}

int List::GetLowSize() const
{
	return Low_size;
}

int List::GetMediumSize() const
{
	return Medium_size;
}

int List::GetHighSize() const
{
	return High_size;
}

bool List::Is_Empty() const//проверка на пустоту
{
	if (Size == 0) {
		return true;
	}
	else {
		return false;
	}
}

pair<int, priority> List::GetHead() const
{
	return pair<int, priority>(head->data, head->pr);
}

ostream& operator<<(ostream& s, const List& p)//выведение всех элементов очереди(с нумерацией) в поток
{
	if (p.Size > 0) {
		int i = 1;
		List::Node* node = p.head;
		do {
			s << i << ") " << node->data;
			if (node->pr == priority::high) {
				s << " high";
			}
			else if (node->pr == priority::medium) {
				s << " medium";
			}
			else {
				s << " low";
			}
			s << "\n";
			i++;
			node = node->pNext;
		} while (node);
		return s;
	}
	else {
		return s << "Queue is empty";
	}
}