
// Beau Duinkerken
// Programming Assignment 6
// 11/27/17

// This program simulates concurrent thread Processing
// Six threads are created and use two shared resources one which has three available instances and one with two
// The six threads must run both of the resource however they can only be ran by one thread at a time

import java.util.logging.Level;
import java.util.logging.Logger;

public class main { // creates two shared resources
	
	// Instantiates resource 1 and 2 from static classes
	static sr1 r1 = new sr1();
	static sr2 r2 = new sr2();
	
	public static void main(String[] args) {
		//create and start 6 threads for 6 concurrent processes
		process Processes[] = new process[6];
		for (int i = 0; i < 6; i++)
		{
			Processes[i] = new process(i, r1, r2); //creates new thread
			Processes[i].start(); //executes the thread
			System.out.println("===== Thread for process_" + i + " created");

		}
	}
}
class sr1 { // creates a class with three instances
	private static int avail1 = 3;
	
	//synchronized methods cannot be interrupted
	//only one thread can access at a time
	public synchronized void acquire(int id) throws InterruptedException
	{
		while (avail1 == 0) {
			System.out.println("+Process_" + id + " is waiting for SR1");
			wait();
		}
		System.out.println("Process_" + id + " acquired SR1.");
		//assigns one of the available instances
		avail1--;
	}
	
	//synchronized methods cannot be interrupted
	//only one thread can access at a time
	public synchronized void release(int id)
	{
		System.out.println("Process_" + id + " released SR1.");
		notify();
		//releases one of the available instances
		avail1++;
	}
}
class sr2 { // creates a class with two instances
	private static int avail2 = 2;
	
	//synchronized methods cannot be interrupted
	//only one thread can access at a time
	public synchronized void acquire(int id) throws InterruptedException
	{
		while (avail2 == 0) {
			System.out.println("+Process_" + id + " is waiting for SR2.");
			wait();
		}
		System.out.println("Process_" + id + " acquired SR2.");
		//assigns one of the available instances
		avail2--;
	}
	
	public synchronized void release(int id)
	{
		System.out.println("Process_" + id + " released SR2.");
		notify();
		//releases one of the available instances
		avail2++;
	}
}
class process extends Thread {
	static sr1 r1;
	static sr2 r2;
	private int id;
	
	//constructor that assigns variables to id, r1, and r2
	public process(int k, sr1 r1, sr2 r2)
	{
		this.r1 = r1;
		this.r2 = r2;
		id = k;
	}
	public void run()
	{
		//acquire r1 and r2
		//display "process_1 is working"
		//release r1 and r2

		try {
			this.r1.acquire(id);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			this.r2.acquire(id);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			Thread.sleep(500);
		}
		catch (InterruptedException ex) {
			Logger.getLogger(process.class.getName()).log(Level.SEVERE, null, ex);
		}
		
		System.out.println("----- Process_" + id + " is working.");
		
		process.r1.release(id);
		process.r2.release(id);
		
		try {
			Thread.sleep(500);
		} catch (InterruptedException ex) {
			Logger.getLogger(process.class.getName()).log(Level.SEVERE, null, ex);
		}		
	}
}

/* Sample Output

Process 0 acquired SR1.
Process 0 acquired SR2.
Thread 0 created
Thread 1 created
Process 1 acquired SR1.
Process 1 acquired SR2.
Thread 2 created
Thread 3 created
Process 2 acquired SR1.
Thread 4 created
Thread 5 created
Process 4 is waiting for SR1
Process 2 is waiting for SR2.
Process 5 is waiting for SR1
Process 3 is waiting for SR1
Process 0 is working.
Process 0 released SR1.
Process 1 is working.
Process 1 released SR1.
Process 4 acquired SR1.
Process 5 acquired SR1.
Process 0 released SR2.
Process 2 acquired SR2.
Process 5 is waiting for SR2.
Process 4 is waiting for SR2.
Process 1 released SR2.
Process 5 acquired SR2.
Process 2 is working.
Process 2 released SR1.
Process 2 released SR2.
Process 3 acquired SR1.
Process 4 acquired SR2.
Process 3 is waiting for SR2.
Process 5 is working.
Process 5 released SR1.
Process 5 released SR2.
Process 3 acquired SR2.
Process 4 is working.
Process 4 released SR1.
Process 4 released SR2.
Process 3 is working.
Process 3 released SR1.
Process 3 released SR2.
*/
