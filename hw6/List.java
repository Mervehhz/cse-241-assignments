import java.util.Iterator;

public interface List<E> extends Collection<E>{

    Iterator<E> iterator();
    boolean add(E e);
    void addAll(Collection c);
    void clear();
    boolean contains(E e);
    boolean containsAll(Collection c);
    boolean isEmpty();
    boolean remove(E e);
    boolean removeAll(Collection c);
    boolean retainAll(Collection c);
    int size();
    void setCollection(E e, int index);
    E getCollection(int index);

}