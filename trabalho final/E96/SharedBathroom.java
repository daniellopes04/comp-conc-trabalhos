import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SharedBathroom {

	public boolean maleOk = true;
	public boolean femaleOk = true;
	
	private int males = 0;
	private int females = 0;
	
	private Lock lock = new ReentrantLock();
	private Condition maleCondition = lock.newCondition();
	private Condition femaleCondition = lock.newCondition();
	
	public void enterMale( ) throws InterruptedException {
		lock.lock();
		try {
			while (femaleOk) {
				maleCondition.await();
			}
			femaleOk = false;
			males++;
		}
		// Aqui usamos finally para gantir que a thread será sempre unlocked.
		finally {
			lock.unlock();
		}
	}
	
	public void enterFemale( ) throws InterruptedException {
		lock.lock();
		try {
			while (maleOk) {
				femaleCondition.await();
			}
			maleOk = false;
			females++;
		}
		// Aqui usamos finally para gantir que a thread será sempre unlocked.
		finally {
			lock.unlock();
		}
	}
	
	public void leaveMale() {
		lock.lock();
		try {
			males--;
			if (males == 0) {
				femaleOk = true;
				femaleCondition.signalAll();
			}
		}
		finally {
			lock.unlock();
		}
	}
	
	public void leaveFemale() {
		lock.lock();
		try {
			females--;
			if (females == 0) {
				maleOk = true;
				maleCondition.signalAll();
			}
		}
		finally {
			lock.unlock();
		}
	}
	
}

class Female extends Thread{
	@Override
	public void run() {
		
	}
}

class Male extends Thread{
	@Override
	public void run() {
		
	}
}