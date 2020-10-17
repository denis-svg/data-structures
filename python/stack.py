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

class Stack:
	length = 0
	def __init__(self):
		self.top = None

	def is_empty(self):
		return self.top == None

	def peek(self):
		if self.is_empty():
			raise IndexError("peek from an empty stack")
		return self.top.get_data()

	def push(self, data):
		node = Node(data)
		node.set_next(self.top)
		self.top = node
		self.length += 1

	def pop(self):
		if self.is_empty():
			raise IndexError("pop from an empty stack")
		data = self.top.get_data()
		self.top = self.top.get_next()
		self.length -= 1
		return data

	def __str__(self):
		s = ""
		current = self.top
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
	s = Stack()
	s.push(4)
	print(s)
	