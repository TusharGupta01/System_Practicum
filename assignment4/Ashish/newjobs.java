// Authors : Ashish Kumar Bedi and Mukarram Tailor
import java.util.*;

//class js exts Th
//	prvate Scanr x;
//	pite in
//	rivate Strin y,o;

class jobs extends Thread
{
	private Scanner x;
	private int p;
	private String y,yo;
	public void job1() throws Exception
	{
		Thread t1 = new Thread(new Runnable()
		{
			public void run()
			{
				x = new Scanner(System.in);
				yo = x.nextLine();
				String var = "[ ]+";
				String[] token = yo.split(var);
				p = Integer.parseInt(token[0]);
				y = token[1];
				System.out.println("Job of T1 ="+p + " " + y);
			}
		});
		Thread t2 = new Thread(new Runnable()
		{
			public void run()
			{
     			int asci;
     			System.out.print("Job of T2 = ");
     			for(int i=0;i<y.length();i++)
     			{
	     			char ch = y.charAt(i);
	   		 		asci = (int)((int)ch+3);
	    			ch = (char)asci;
	    			System.out.print(ch);
     			}
     			System.out.println();
			}
		});
		Thread t3  = new Thread(new Runnable()
		{
			public void run()
			{
					System.out.print("Job of T3 = ");
					int q=1;
					long temp=0;
					long arr[] = new long[2];
					arr[0] =0;
					arr[1] =1;
					if(p==0 || p==1)
					{
						System.out.println(p);
					}
					else
					{
						while(q<p)
						{
							temp = arr[0]+arr[1];
							arr[0] = arr[1];
							arr[1] = temp;
							q++;
						}
						System.out.println(temp);
					}
			}
		});
		Thread t4 = new Thread(new Runnable()
		{
			public void run()
			{
				int asci;
				System.out.print("Job of T4 = ");
			    int q=1;
			    long temp=0;
				long arr[] = new long[2];
				arr[0] =0;
				arr[1] =1;
				if(p==0 || p==1)
				{
					System.out.println(p+"  ");
				}
				else
				{
					while(q<p)
					{
						temp = arr[0]+arr[1];
						arr[0] = arr[1];
						arr[1] = temp;
						q++;
					}
				}
				System.out.print(temp + "  ");
				for(int i=0;i<y.length();i++)
     			{
	     			char ch = y.charAt(i);
	   		 		asci = (int)((int)ch+3);
	    			ch = (char)asci;
	    			System.out.print(ch);
     			}
				System.out.println();
			}
		});
		t1.start();
		t1.join();
		t2.start();
		t2.join();
		t3.start();
		t3.join();
		t4.start();
		t4.join();
	}
}
