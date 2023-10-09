import java.util.ArrayList;
import java.util.List;

public class LinkedList {
    public Node root = null;

    synchronized void deleteNode(int exponent) {
        Node temp = root, prev = null;
        if (temp != null && temp.value.exponent == exponent) {
            root = temp.nextNode;
            return;
        }
        while (temp != null && temp.value.exponent != exponent) {
            prev = temp;
            temp = temp.nextNode;
        }
        if (temp == null)
            return;

        prev.nextNode = temp.nextNode;
    }

    synchronized public void addTerm(Node newNode) {
        if (root == null) {
            root = newNode;
            return;
        }

        //exp newNode > exp root => newNode devine root
        if (newNode.value.exponent > root.value.exponent) {
            newNode.nextNode = root;
            root = newNode;
            return;
        }

        //exponenti egali => se aduna coeficientii
        if (newNode.value.exponent == root.value.exponent) {
            root.value.coefficient += newNode.value.coefficient;
            return;
        }

        Node previousNode = root, currentNode = root.nextNode;
        while (currentNode != null) {
            if (newNode.value.exponent > currentNode.value.exponent) {
                newNode.nextNode = currentNode;
                previousNode.nextNode = newNode;
                return;
            }

            if (newNode.value.exponent == currentNode.value.exponent) {
                currentNode.value.coefficient += newNode.value.coefficient;

                if(currentNode.value.coefficient == 0)
                    deleteNode(currentNode.value.exponent);
                return;
            }
            previousNode = currentNode;
            currentNode = currentNode.nextNode;
        }

        previousNode.nextNode = newNode;
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