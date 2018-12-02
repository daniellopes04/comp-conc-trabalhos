class WriteLock implements Lock {

  SimpleReadWriteLock lock;

  public WriteLock(SimpleReadWriteLock obj){
    lock = obj;
  }
  
  public void lock() throws InterruptedException {
    synchronized(lock) {
      while (lock.readers > 0 || lock.writer) {
        wait();
      }
      lock.writer = true;
    }
  }

  public void unlock() throws InterruptedException {
    synchronized(lock) {  
      lock.writer = false;
      lock.notifyAll();
    }
  }
}