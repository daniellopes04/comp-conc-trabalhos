class ReadLock implements Lock {
  
  SimpleReadWriteLock lock;

  public ReadLock(SimpleReadWriteLock obj){
    lock = obj;
  }
  
  public void lock() throws InterruptedException {
    synchronized(lock){
      while (lock.writer) {
        wait();
      }
      lock.readers++;
    }
  }

  public void unlock() {
    synchronized(lock){
      lock.readers--;
      if (lock.readers == 0)
        lock.notifyAll();
    }
  }
}