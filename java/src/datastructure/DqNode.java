package datastructure;

class DqNode<T>{
    private DqNode<T> next;
    private DqNode<T> previous;
    private T data;
    public DqNode(T data){
        this.next = null;
        this.previous = null;
        this.data = data;
    }
    public void setData(T data){
        this.data = data;
    }
    public void setNext(DqNode<T> next){
        this.next = next;
    }
    public void setPrevious(DqNode<T> previous){
        this.previous = previous;
    }
    public T getData(){
        return this.data;
    }
    public DqNode<T> getNext(){
        return this.next;
    }
    public DqNode<T> getPrevious(){
        return this.previous;
    }
}
