package datastructure;

public class Queue<T> {
    private Node<T> top;
    private Node<T> head;
    private int length;
    public Queue(){
        this.length = 0;
        this.top = null;
        this.head = null;
    }
    public T peek(){
        return this.head.getData();
    }
    public boolean isEmpty(){
        return this.head == null;
    }
    public void push(T data){
        Node<T>temp = new Node<T>(data);
        if (this.isEmpty()){
            this.top = temp;
            this.head = temp;
        }else{
            this.top.setNext(temp);
            this.top = temp;
        }
        this.length++;
    }
    public T pop(){
        if (this.isEmpty()){
            throw new IndexOutOfBoundsException("pop from an empty queue");
        }
        T data = this.head.getData();
        this.head = this.head.getNext();
        this.length--;
        return data;
    }
    public int getLength(){
        return this.length;
    }
    public void log(){
        Node<T> current = this.head;
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
