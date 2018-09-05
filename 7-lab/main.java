/* joshua holland
 * CSCI 117 Program 6(i think)
 * 
 * This program simulates concurrent thread processing. Six threads are
 * created, which each have access to two shared resources. These shared
 * resources have three and two slots available for usage. The resources
 * can only be operated on by one process at a time, and must be released
 * before another process can use the resource.
*/

import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * This class creates two static shared resources which will be used in the
 * threads
 */
public class main {
	
	// Instantiates resource 1 and 2 from static classes
	static sr1 r1 = new sr1();
	static sr2 r2 = new sr2();
	
	public static void main(String[] args) {
		// Create and start 6 threads for 6 concurrent processes
		// Processes are made as an array for cleaner code and organization
		process Processes[] = new process[6];
		
		// Loops through each of the threads and executes them
		// Notifies the user that the thread has been started
		for (int i = 0; i < 6; i++)
		{
			Processes[i] = new process(i, r1, r2); // Creates new thread
			Processes[i].start(); // Executes the thread
			System.out.println("Thread for process " + i + " created!");
		}
	}

}
/*
 * Creates a class with three open slots for processing.
 * This means that three threads can access this shared resource at a time.
 */
class sr1 {
	private static int avail1 = 3;
	
	// Synchronized methods cannot be interrupted
	// Only one thread can access at a time
	public synchronized void acquire(int id) throws InterruptedException
	{
		while (avail1 == 0) {
			System.out.println("+Process " + id + " is waiting for SR1.");
			// Uses the wait() function to delay the program during looping
			wait();
		}
		System.out.println("Process " + id + " acquires SR1.");
		
		// Allocates one of the available slots to the thread
		avail1--;
	}
	
	// Synchronized methods cannot be interrupted
	// Only one thread can access at a time
	public synchronized void release(int id)
	{
		System.out.println("Process " + id + " releases SR1.");
		// Wakes up the thread that was waiting
		notify();
		
		// Returns one of the available slots from the thread
		avail1++;
	}
}
/*
 * Creates a class with two open slots for processing.
 * This means that two threads can access this shared resource at a time.
 */
class sr2 {
	private static int avail2 = 2;
	
	// Synchronized methods cannot be interrupted
	// Only one thread can access at a time
	public synchronized void acquire(int id) throws InterruptedException
	{
		while (avail2 == 0) {
			System.out.println("+Process " + id + " is waiting for SR2.");
			// Uses the wait() function to delay the program during looping
			wait();
		}
		
		System.out.println("Process " + id + " acquires SR2.");
		// Allocates one of the available slots to the thread
		avail2--;
	}
	
	public synchronized void release(int id)
	{
		System.out.println("Process " + id + " releases SR2.");
		// Wakes up the thread that was waiting
		notify();
		// Returns one of the available slots from the thread
		avail2++;
	}
}
/*
 * The process class extends from Thread since it requires the usages
 * of methods such as acquire() and sleep(). Extending the process class
 * from Thread also gives process access to the data members throughout
 * the entire program.
 */
class process extends Thread {
	static sr1 r1;
	static sr2 r2;
	private int id;
	
	// Constructor that assigns variables to id, r1, and r2
	public process(int k, sr1 r1, sr2 r2)
	{
		this.r1 = r1;
		this.r2 = r2;
		id = k;
	}
	
	// The threads that are being executed are run through this program.
	// First, r1 and r2 are acquired. The program then causes the thread
	// to briefly sleep. After the brief sleep, r1 and r2 are released,
	// and the thread is forced to sleep again.
	// Note that each operation has a try/catch structure that handles
	// the case where the thread cannot be acquired/slept/released
	public void run()
	{
		// Acquire r1 and r2
		// Display "process_1 is working"
		// Release r1 and r2

		try {
			process.r1.acquire(id);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			process.r2.acquire(id);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			Thread.sleep(500);
		}
		catch (InterruptedException ex) {
			Logger.getLogger(process.class.getName()).log(Level.SEVERE, null, ex);
		}
		
		System.out.println(" ----Process " + id + " is working.");
		
		process.r1.release(id);
		process.r2.release(id);
		
		try {
			Thread.sleep(500);
		} catch (InterruptedException ex) {
			Logger.getLogger(process.class.getName()).log(Level.SEVERE, null, ex);
		}		
	}
}

/*
|------------OUTPUT------------|
Thread for process 0 created!
Process 0 acquires SR1.
Process 0 acquires SR2.
Thread for process 1 created!
Process 1 acquires SR1.
Process 1 acquires SR2.
Process 2 acquires SR1.
+Process 2 is waiting for SR2.
Thread for process 2 created!
Thread for process 3 created!
Thread for process 4 created!
+Process 3 is waiting for SR1.
Thread for process 5 created!
+Process 4 is waiting for SR1.
+Process 5 is waiting for SR1.
 ----Process 0 is working.
Process 0 releases SR1.
Process 0 releases SR2.
Process 3 acquires SR1.
Process 2 acquires SR2.
+Process 3 is waiting for SR2.
 ----Process 1 is working.
Process 1 releases SR1.
Process 1 releases SR2.
Process 4 acquires SR1.
Process 3 acquires SR2.
+Process 4 is waiting for SR2.
 ----Process 2 is working.
Process 2 releases SR1.
Process 2 releases SR2.
Process 5 acquires SR1.
Process 4 acquires SR2.
+Process 5 is waiting for SR2.
 ----Process 3 is working.
Process 3 releases SR1.
Process 3 releases SR2.
Process 5 acquires SR2.
 ----Process 4 is working.
Process 4 releases SR1.
Process 4 releases SR2.
 ----Process 5 is working.
Process 5 releases SR1.
Process 5 releases SR2.
*/
