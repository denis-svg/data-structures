class Node:
	def __init__(self, data):
		self.data = data
		self.next = None

	def set_data(self, new_data):
		self.data = new_data

	def get_data(self):
		return self.data

	def set_next(self, new_next):
		self.next = new_next

	def get_next(self):
		return self.next

class Queue:
	length = 0
	def __init__(self):
		self.head = None
		self.top = None

	def is_empty(self):
		return self.head == None

	def peek(self):
        if self.is_empty():
			raise IndexError("peek from an empty stack")
		return self.top.get_data()

	def push(self, data):
		node = Node(data)
		if self.is_empty():
			self.head = node
			self.top = node
		else:
			self.top.set_next(node)
			self.top = node
		self.length += 1

	def pop(self):
		if self.is_empty():
			raise IndexError("pop from an empty queue")
		data = self.head.get_data()
		self.head = self.head.get_next()
		self.length -= 1

		return data

	def __str__(self):
		s = ""
		current = self.head
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
	q = Queue()
	q.push(4)
	q.push('12')
	print(len(q))
