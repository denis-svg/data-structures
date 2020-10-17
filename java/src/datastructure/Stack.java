package datastructure;

public class Stack<T> {
    private Node<T> top;
    private int length;
    public Stack(){
        top = null;
        this.length = 0;
    }
    public boolean isEmpty(){
        return top == null;
    }
    public T peek(){
        return this.top.getData();
    }
    public void push(T data){
        this.top = new Node<>(data, this.top);
        this.length++;
    }
    public T pop(){
        if (this.length == 0)
            throw new IndexOutOfBoundsException("pop from an empty stack");
        T data = this.top.getData();
        this.top = this.top.getNext();
        this.length--;
        return data;
    }
    public int getLength(){
        return this.length;
    }
    public void log(){
        Node<T> current = this.top;
        System.out.print("[");
        int index = 0;
        while (current != null){
            if (index + 1 == this.length)
                System.out.print(current.getData());
            else {
            System.out.print(current.getData());
            System.out.print(", ");
            }
            current = current.getNext();
            index++;
        }
        System.out.print("]\n");
    }
}
