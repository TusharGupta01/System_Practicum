// Authors : Ashish Kumar Bedi and Mukarram Tailor
import java.util.*;
// 2nd test case code
//class matrices
//
//	private Scner x;
//	private int y;

class matrices
{
	private Scanner x;
	private int y;
	private int mat[][] = new int[5000][5000];
	public void size()
	{
		x =new Scanner(System.in);
		y = x.nextInt();
	}
	public void get()
	{
		for(int i=1;i<=y;i++)
		{
			for(int j=1;j<=y;j++)
			{
				if((j%2)==0)
				{
					mat[i][j] = 1;
				}
				else
				{
					mat[i][j] = 2;
				}
			}
		}
		for(int i=1;i<=y;i++)
		{
			for(int j=1;j<=y;j++)
			{
				System.out.print(mat[i][j]+ " ");
			}
			System.out.println();
		}
	}
	public void multiplication()
	{
		int product_mat[][] = new int[y+1][y+1],z=0;
		for(int i=1;i<=y;i++)
		{
			for(int j=1;j<=y;j++)
			{
				for(int k=1;k<=y;k++)
				{
					z += mat[i][k]*mat[k][j];
				}
				product_mat[i][j] = z;
				z=0;
			}

		}
		for(int i=1;i<=y;i++)
		{
			for(int j=1;j<=y;j++)
			{
				System.out.print(product_mat[i][j]+ "    ");
			}
			System.out.println();
		}
	}
}
