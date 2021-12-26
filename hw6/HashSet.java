import java.io.Serializable;
import java.util.Iterator;

public class Hashset<E> implements Set<E>,  Cloneable, Serializable {

    private E[] set;

    public HashSet<E> (){

        set = (E[]) new Object[1];
    }

    /*public HashSet<E> (Collection c){

        if(!c.isEmpty())
            addAll(c);
    }*/

    public void setCollection(E e, int index){

        set[index] = e;
    }

    public E getCollection(int index){

        return set[index];
    }

    public Iterator<E> iterator(){

        Iterator<E> it = new Iterator<E>();

        return it;
    }

    public int size() {

        int setSize = 0;

        for(int i=0;set[i] != null;i++)
            setSize++;

        return setSize;
    }

    public boolean isDuplicateElement(E e){

        for(int i=0;i<this.size();i++)
            if(set[i] == e)
                return false;
        
        return true;
    }

    public boolean add(E e){

        if(isDuplicateElement(e)){
            set[this.size() + 1] = e;

            return true;
        }
        else 
            return false;
    }

    public void addAll(Collection c){

        for(int i=0;i<c.size();i++)
            add((E)c.getCollection(i));
    }

    public void clear(){

        for(int i=0;i<this.size();i++)
            remove(set[i]);
    }

    public boolean contains(E e){

        return !isDuplicateElement(e);
    }

    public boolean containsAll(Collection c){

        for(int i=0;i<c.size();i++)
            if(!contains((E)c.getCollection(i)))
                return false;

        return true;
    }

    public boolean isEmpty(){

        return (this.size() == 0 ? true : false);
    }

    public boolean remove(E e){

        for(int i=0;i<this.size();i++)
            if(set[i] == e)

    }

    public boolean removeAll(Collection c){


    }

    public boolean retainAll(Collection c){


    }
}