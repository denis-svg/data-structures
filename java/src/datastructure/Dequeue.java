package datastructure;

public class Dequeue<T>{
    private DqNode<T> front;
    private DqNode<T> rear;
    private int length;
    public Dequeue(){
        this.front = null;
        this.rear = null;
        this.length = 0;
    }

    public boolean isEmpty(){
        return this.front == null;
    }
        
    public void addFront(T value){
        DqNode<T> new_node = new DqNode<T>(value);
        if (this.length == 0){
            this.front = new_node;
            this.rear = new_node;
        }else{
            new_node.setNext(this.front);
            this.front.setPrevious(new_node);
            this.front = new_node;
        }
        this.length++;
    }    

    public void addRear(T value){
        DqNode<T> new_node = new DqNode<T>(value);
        if (this.length == 0){
            this.front = new_node;
            this.rear = new_node;
        }else{
            new_node.setPrevious(this.rear);
            this.rear.setNext(new_node);
            this.rear = new_node;
        }
        this.length++;
    }

    public T removeFront(){
        if (this.isEmpty())
            throw new IndexOutOfBoundsException("remove from an empty Dequeue");
        else if (this.length == 1){
            T data = this.front.getData();
            this.front = null;
            this.rear = null;
            this.length--;
            return data;
        }else{
            T data = this.front.getData();
            this.front = this.front.getNext();
            this.front.setPrevious(null);
            this.length--;
            return data;
        }
    }

    public T removeRear(){
        if (this.isEmpty())
            throw new IndexOutOfBoundsException("remove from an empty Dequeue");
        else if (this.length == 1){
            T data = this.rear.getData();
            this.front = null;
            this.rear = null;
            this.length--;
            return data;
        }else{
            T data = this.rear.getData();
            this.rear = this.rear.getPrevious();
            this.rear.setNext(null);
            this.length--;
            return data;
        }
    }
    
    public int getLength(){
        return this.length;
    }
    
    public void log(){
        DqNode<T> current = this.front;
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
