import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SavingsAccount {

	private int balance = 0;
	
	private Lock lock = new ReentrantLock();
	private Condition deposited = lock.newCondition();
	private Condition preferredHandled = lock.newCondition();
	private int preferredCount = 0;
	
	public void depoist(int k) {
		lock.lock();
		try {
			balance += k;
			deposited.notifyAll();
		}
		finally {
			lock.unlock();
		}
	}
	
	public void withdraw(int k, boolean preferred) throws InterruptedException {
		lock.lock();
		try {
			if (!preferred){
				while (k > balance) {
					deposited.await();
					
					while (preferredCount > 0) {
						preferredHandled.await();
					}
				}
			}
			else{
				preferredCount++;
				while (k > balance) {
					deposited.await();
				}
				preferredCount--;
				preferredHandled.notifyAll();
			}
			balance -= k;
		}
		finally {
			lock.unlock();
		}
	}
}
