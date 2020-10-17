class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.previous = None

    def set_data(self, data):
        self.data = data

    def get_data(self):
        return self.data
    
    def set_next(self, next):
        self.next = next
    
    def get_next(self):
        return self.next

    def set_previous(self, previous):
        self.previous = previous

    def get_previous(self):
        return self.previous

class Dequeue:
    def __init__(self):
        self.length = 0
        self.front = None
        self.rear = None

    def is_empty(self):
        return self.front == None

    def add_rear(self, data):
        self.length += 1
        new_node = Node(data)
        if self.is_empty():
            self.rear = new_node
            self.front = new_node
        else:
            self.rear.set_next(new_node)
            new_node.set_previous(self.rear)
            self.rear = new_node
    
    def add_front(self, data):
        self.length += 1
        new_node = Node(data)
        if not self.is_empty():
            self.front.set_previous(new_node)
            new_node.set_next(self.front)
            self.front = new_node
        else:
            self.front = new_node
            self.rear = new_node

    def remove_rear(self):
        if self.is_empty():
            raise IndexError("pop from an empty dequeue")
        if self.length != 1:
            data = self.rear.get_data()
            self.rear.previous.next = None
            self.rear = self.rear.get_previous()
        else:
            data = self.rear.get_data()
            self.rear = None
            self.front = None
        self.length -= 1
        return data

    def remove_front(self):
        if self.is_empty():
            raise IndexError("pop from an empty dequeue")
        if self.length != 1:
            data = self.front.get_data()
            self.front.next.previous = None
            self.front = self.front.get_next()
        else:
            data = self.front.get_data()
            self.rear = None
            self.front = None
        self.length -= 1
        return data

    def __str__(self):
		s = ""
		current = self.front
		while current != None:
			if current.get_next() == None:
				s += str(current.get_data())
				break 
			s += str(current.get_data()) + ", "
			current = current.get_next()

		return '[' + s + ']'

    def __len__(self):
        return self.length

if __name__ == "__main__":
    d = Dequeue()
    d.add_rear("das")
    d.add_rear(5)
    d.add_rear(6)
    print(len(d))