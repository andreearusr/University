import java.util.ArrayList;
import java.util.List;

public class LinkedList {
    public Node root = null;

    public void addTerm(Node newNode) {
        if (root == null || newNode.value.exponent > root.value.exponent) {
            newNode.nextNode = root;
            root = newNode;
            return;
        }

        Node prevNode = null;
        Node currentNode = root;

        currentNode.lock();
        while (currentNode.nextNode != null && currentNode.nextNode.value.exponent >= newNode.value.exponent) {
            if(prevNode != null) {
                prevNode.unlock();
            }
            prevNode = currentNode;
            currentNode = currentNode.nextNode;
            currentNode.lock();
        }

        //exponenti egali => se aduna coeficientii
        if (currentNode.value.exponent == newNode.value.exponent) {
            currentNode.value.coefficient += newNode.value.coefficient;

            //coeficientul devine 0 => stergere nod
            if (currentNode.value.coefficient == 0) {
                if (prevNode == null) root = currentNode.nextNode;
                else prevNode.nextNode = currentNode.nextNode;
            }
        }
        
        //adauga nod intre current si nextNode-ul currentului
        else {
            newNode.nextNode = currentNode.nextNode;
            currentNode.nextNode = newNode;
        }

        if(prevNode != null) {
            prevNode.unlock();
        }
        currentNode.unlock();
    }

    List<Term> asList() {
        List<Term> terms = new ArrayList<>();
        Node currentNode = root;
        while (currentNode != null) {
            terms.add(currentNode.value);
            currentNode = currentNode.nextNode;
        }
        return terms;
    }
}