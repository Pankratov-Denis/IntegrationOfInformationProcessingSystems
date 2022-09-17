class QuickSortStack
{
private:
    struct StackItem // Границы сегмента
    {
        int left;
        int right;
    };
    StackItem *body; // Адрес начала области в памяти,
    // где хранится массив с элементами стека
    int size; // Размер массива body
    int top; // Вершина стека

public:
    QuickSortStack(int);
    ~QuickSortStack();

    void push(int,int);
    void pop (int&, int&);
    int isEmpty();
};
