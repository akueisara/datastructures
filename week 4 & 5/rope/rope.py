# http://ideone.com/flSA8K
import sys, random
 
class Node:
	def __init__(v, x, y, l, r):
		v.size, v.x, v.y, v.l, v.r = 1, x, y, l, r
	def calc(v):
		v.size = v.l.size + v.r.size + 1
	@staticmethod
	def init():
		p = Node(0, 0, None, None)
		p.size = 0
		Node.nul = p.l = p.r = p
		Node.cnt = 0
Node.init()
 
class Rope:
	@staticmethod
	def split(t, k):
		if t == Node.nul:
			return (Node.nul, Node.nul)
		if t.l.size < k:
			(l, r) = Rope.split(t.r, k - t.l.size - 1)
			t.r = l
			t.calc()
			return (t, r)
		else:
			(l, r) = Rope.split(t.l, k)
			t.l = r
			t.calc()
			return (l, t)
 
	@staticmethod
	def merge(l, r):
		if l == Node.nul:
			return r
		if r == Node.nul:
			return l
		if l.y < r.y:
			l.r = Rope.merge(l.r, r)
			l.calc()
			return l
		else:
			r.l = Rope.merge(l, r.l)
			r.calc()
			return r
 
	@staticmethod
	def out(t, buf):
		if t == Node.nul:
			return
		Rope.out(t.l, buf)
		buf.append(t.x)
		Rope.out(t.r, buf)
 
	def result(self):
		buf = []
		Rope.out(self.root, buf)
		return "".join(buf)
 
	def __init__(self, s):
		self.root = Node.nul
		for c in s:
			self.root = Rope.merge(self.root, Node(c, random.randint(0, 1 << 30), Node.nul, Node.nul))
 
	def process(self, i, j, k):
		j += 1
		(l, r) = Rope.split(self.root, i)
		(m, r) = Rope.split(r, j - i)
		(l, r) = Rope.split(Rope.merge(l, r), k)
		self.root = Rope.merge(Rope.merge(l, m), r)
 
s = sys.stdin.readline().strip()
rope = Rope(s)
q = int(sys.stdin.readline())
for _ in range(q):
	i, j, k = map(int, sys.stdin.readline().strip().split())
	rope.process(i, j, k)
print(rope.result())