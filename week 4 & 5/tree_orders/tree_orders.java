import java.util.*;
import java.io.*;

public class tree_orders {
    class FastScanner {
		StringTokenizer tok = new StringTokenizer("");
		BufferedReader in;

		FastScanner() {
			in = new BufferedReader(new InputStreamReader(System.in));
		}

		String next() throws IOException {
			while (!tok.hasMoreElements())
				tok = new StringTokenizer(in.readLine());
			return tok.nextToken();
		}
	
		int nextInt() throws IOException {
			return Integer.parseInt(next());
		}
	}

	public class TreeOrders {
		int n;
		int[] key, left, right;
		ArrayList<Integer> result;
		
		void read() throws IOException {
			FastScanner in = new FastScanner();
			n = in.nextInt();
			key = new int[n];
			left = new int[n];
			right = new int[n];
			for (int i = 0; i < n; i++) { 
				key[i] = in.nextInt();
				left[i] = in.nextInt();
				right[i] = in.nextInt();
			}
		}

		List<Integer> inOrder() {
			result = new ArrayList<Integer>();
			inOrderTraversal(0);      
			return result;
		}
		
        void inOrderTraversal(int index) {
            if (left[index] != -1)
                inOrderTraversal(left[index]);
            result.add(key[index]);
            if (right[index] != -1)
                inOrderTraversal(right[index]);
		}

		List<Integer> preOrder() {
			result = new ArrayList<Integer>();
            preOrderTraversal(0);      
			return result;
		}
		
		void preOrderTraversal(int index) {
			result.add(key[index]);
            if (left[index] != -1)
                preOrderTraversal(left[index]);
            if (right[index] != -1)
                preOrderTraversal(right[index]);
		}

		List<Integer> postOrder() {
			result = new ArrayList<Integer>();
            postOrderTraversal(0);    
			return result;
		}
		
		void postOrderTraversal(int index) {
            if (left[index] != -1)
                postOrderTraversal(left[index]);
            if (right[index] != -1)
                postOrderTraversal(right[index]);
			result.add(key[index]);
		}
	}

	static public void main(String[] args) throws IOException {
            new Thread(null, new Runnable() {
                    public void run() {
                        try {
                            new tree_orders().run();
                        } catch (IOException e) {
                        }
                    }
                }, "1", 1 << 26).start();
	}

	public void print(List<Integer> x) {
		for (Integer a : x) {
			System.out.print(a + " ");
		}
		System.out.println();
	}

	public void run() throws IOException {
		TreeOrders tree = new TreeOrders();
		tree.read();
		print(tree.inOrder());
		print(tree.preOrder());
		print(tree.postOrder());
	}
}
