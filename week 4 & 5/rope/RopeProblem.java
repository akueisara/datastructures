// can't solve it in Java... QQ

import java.io.*;
import java.util.*;

class RopeProblem {
    class FastScanner {
        StringTokenizer tok = new StringTokenizer("");
        BufferedReader in ;

        FastScanner() { in = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (!tok.hasMoreElements())
                tok = new StringTokenizer( in .readLine());
            return tok.nextToken();
        }
        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
    }

    class Vertex {
        char key;
        long size;
        Vertex left;
        Vertex right;
        Vertex parent;

        Vertex(char key, long size, Vertex left, Vertex right, Vertex parent) {
            this.key = key;
            this.size = size;
            this.left = left;
            this.right = right;
            this.parent = parent;
        }
    }

    class Rope {
        private String s;
        private Vertex root;


        Rope(String s) {
            this.s = s;
            this.root = null;
            for (int i = 0; i < s.length(); i++) {
                Vertex next = new Vertex(s.charAt(i), 1, null, null, null);
                root = merge(root, next);
            }
        }

        void update(Vertex v) {
            if (v == null)
                return;
            v.size = 1 + (v.left != null ? v.left.size : 0) + (v.right != null ? v.right.size : 0);
            if (v.left != null) {
                v.left.parent = v;
            }
            if (v.right != null) {
                v.right.parent = v;
            }
        }

        void smallRotation(Vertex v) {
            Vertex parent = v.parent;
            if (parent == null) {
                return;
            }
            Vertex grandparent = v.parent.parent;
            if (parent.left == v) {
                Vertex m = v.right;
                v.right = parent;
                parent.left = m;
            } else {
                Vertex m = v.left;
                v.left = parent;
                parent.right = m;
            }
            update(parent);
            update(v);
            v.parent = grandparent;
            if (grandparent != null) {
                if (grandparent.left == parent) {
                    grandparent.left = v;
                } else {
                    grandparent.right = v;
                }
            }
        }

        void bigRotation(Vertex v) {
            if (v.parent.left == v && v.parent.parent.left == v.parent) {
                // Zig-zig
                smallRotation(v.parent);
                smallRotation(v);
            } else if (v.parent.right == v && v.parent.parent.right == v.parent) {
                // Zig-zig
                smallRotation(v.parent);
                smallRotation(v);
            } else {
                // Zig-zag
                smallRotation(v);
                smallRotation(v);
            }
        }

        void splay(Vertex root, Vertex v) {
            if (v == null)
                return;
            while (v.parent != null) {
                if (v.parent.parent == null) {
                    smallRotation(v);
                    break;
                }
                bigRotation(v);
            }
            root = v;
        }

        Vertex find(Vertex root, int leftNum) {
            Vertex v = root;

            while (v != null) {
                int s = (v.left != null) ? v.left.size : 0;
                if (leftNum == (s + 1)) {
                    break;
                } else if (leftNum < (s + 1)) {
                    v = v.left;
                } else if (leftNum > (s + 1)) {
                    v = v.right;
                    leftNum = leftNum - s - 1;
                }
            }
            splay(root, v);
            return v;
        }

        void split(Vertex root, int key, Vertex left, Vertex right) {
            right = find(root, key);
            splay(root, right);
            if (right == null) {
                left = root;
                return;
            }
            left = right.left;
            right.left = null;
            if (left != null) {
                left.parent = null;
            }
            update(left);
            update(right);
        }

        Vertex merge(Vertex left, Vertex right) {
            if (left == null)
                return right;
            if (right == null)
                return left;
            Vertex minRight = right;
            while (minRight.left != null) {
                minRight = minRight.left;
            }
            splay(right, minRight);
            right.left = left;
            update(right);
            return right;
        }

        void insert(Vertex root, int k, Vertex subString) {
            Vertex left = null;
            Vertex right = null;
            split(root, k, left, right);
            root = merge(merge(left, subString), right);
        }

        String traversalInOrder(Vertex root) {
			StringBuilder str = new StringBuilder();
            if (root == null) {
                return str.toString();
            }
            Stack < Vertex > S = new Stack < Vertex > ();
            Vertex p = root;
            while (p != null) {
                S.push(p);
                p = p.left;
            }
            while (!S.empty()) {
                p = S.peek();
                str.append(p.key);
                S.pop();
                p = p.right;
                while (p != null) {
                    S.push(p);
                    p = p.left;
                }
            }
            return str.toString();
        }

        void process_naive(int i, int j, int k) {
            String t = s.substring(0, i) + s.substring(j + 1);
            s = t.substring(0, k) + s.substring(i, j + 1) + t.substring(k);
        }

        void process(int i, int j, int k) {
            Vertex left = null;
            Vertex right = null;
            Vertex middle = null;
            split(root, i + 1, left, middle);
            split(middle, j - i + 2, middle, right);
            root = merge(left, right);
            insert(root, k + 1, middle);
        }

        String result() {
            s = traversalInOrder(root);
            return s;
        }

    }

    public static void main(String[] args) throws IOException {
        new RopeProblem().run();
    }
    public void run() throws IOException {
        FastScanner in = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);
        Rope rope = new Rope( in .next());
        for (int q = in .nextInt(); q > 0; q--) {
            int i = in .nextInt();
            int j = in .nextInt();
            int k = in .nextInt();
            rope.process(i, j, k);
        }
        out.println(rope.result());
        out.close();
    }
}