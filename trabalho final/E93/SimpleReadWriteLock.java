public class SimpleReadWriteLock implements ReadWriteLock {
  
  public int readers;
  public boolean writer;
  Lock readLock, writeLock;

  public SimpleReadWriteLock() {
    writer = false;
    readers = 0;
    readLock = new ReadLock(this);
    writeLock = new WriteLock(this);
  }

  public Lock readLock() {
    return readLock;
  }

  public Lock writeLock() {
    return writeLock;
  }
}