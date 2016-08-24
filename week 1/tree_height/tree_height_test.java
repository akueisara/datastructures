import java.util.*;
import java.io.*;

public class tree_height_test {
	static int filenumber = 1;
	
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

	public class TreeHeight {
		int n;
		int parent[];
		
		void read() throws IOException {
			FileReader fr1, fr2;
			int result;
			String fileNameWithZero = ".\\tests\\0" + filenumber;
			String fileNameWithoutZero = ".\\tests\\" + filenumber;
			try {
				if(filenumber<10) {
					fr1 = new FileReader(fileNameWithZero);
					fr2 = new FileReader(fileNameWithZero + ".a");
				}
				else {
					fr1 = new FileReader(fileNameWithoutZero);
					fr2 = new FileReader(fileNameWithoutZero + ".a");
				}
				BufferedReader bf1 = new BufferedReader(fr1);
				BufferedReader bf2 = new BufferedReader(fr2);
				n = Integer.parseInt(bf1.readLine());
				parent = new int[n];
				String[] strParent = bf1.readLine().split(" ");
				for (int j = 0; j < n; j++) {
					parent[j] = Integer.parseInt(strParent[j]);
				}
				result = Integer.parseInt(bf2.readLine());
				bf1.close();
				bf2.close();
				long start = System.currentTimeMillis();
				int fast   = computeHeight();
				long end   = System.currentTimeMillis();
				long time = (end - start)/1000;
				if(fast == result && time < 6)
					System.out.println(filenumber + " Pass");
				filenumber++;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		int computeHeight() {
			int maxHeight = 0;
			int[] heights = new int[parent.length];
			for (int vertex = 0; vertex < n; vertex++) {
				if (heights[vertex] != 0)
					continue;
				int height = 0;
				for (int i = vertex; i != -1; i = parent[i]) {
					if (heights[i] != 0) {
						height += heights[i];   
						break;
					}
					height++;
				}
				maxHeight = Math.max(maxHeight, height);
				for (int i = vertex; i != -1; i = parent[i]) {
					if (heights[i] != 0)
						break;
					heights[i] = height--;
				}
			}
			return maxHeight;
		}
	
		int old_computeHeight() {
			int maxHeight = 0;
			for (int vertex = 0; vertex < n; vertex++) {
				int height = 0;
				for (int i = vertex; i != -1; i = parent[i])
					height++;
				maxHeight = Math.max(maxHeight, height);
			}
			return maxHeight;
		}
	}

	static public void main(String[] args) throws IOException {
            new Thread(null, new Runnable() {
                    public void run() {
                        try {
                            new tree_height_test().run();
                        } catch (IOException e) {
                        }
                    }
                }, "1", 1 << 26).start();
	}
	
	public void run() throws IOException {
		TreeHeight tree = new TreeHeight();
		for(int i=1;i<=24;i++) {
			tree.read();			
		}
		
	}
}
