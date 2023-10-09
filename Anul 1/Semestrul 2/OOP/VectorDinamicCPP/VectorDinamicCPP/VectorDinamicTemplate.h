#pragma once
/*
template <typename ElementT>
class IteratorVectorT;

template <typename ElementT>
class VectDinNewDeleteT
{
public:
	/*
	Constructor default
	Alocam loc pentru 5 elemente
	*/
	//VectDinNewDeleteT();

	/*
	Constructor de copiere
	*/
	//VectDinNewDeleteT(const VectDinNewDeleteT& ot); //rule of 3

	/*
	Eliberam memoria
	*/
	//~VectDinNewDeleteT();//rule of 3

	/*
	Operator assgnment
	elibereaza ce era in obiectul curent (this)
	aloca spatiu pentru elemente
	copieaza elementele din ot in this
	*/
	//VectDinNewDeleteT& operator=(const VectDinNewDeleteT& ot);//rule of 3


	/*
	Move constructor
	Apelat daca construim un nou vector dintr-un r-value (ex temporary, expresie de la return)
	Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
	*/
	//VectDinNewDeleteT(VectDinNewDeleteT&& ot); //rule of 5 

	/*
	Move assignment
	Similar cu move constructor
	Folosit la assignment
	*/
	//VectDinNewDeleteT& operator=(VectDinNewDeleteT&& ot); //rule of 5 

/*
	void add(const ElementT& el);

	ElementT& get(int poz) const;

	void set(int poz, const ElementT& el);

	int size() const noexcept;

	friend class IteratorVectorT<ElementT>;
	//functii care creaza iteratori
	IteratorVectorT<ElementT> begin();
	IteratorVectorT<ElementT> end();


private:
	int lg;//numar elemente
	int cap;//capacitate
	ElementT* elems;//elemente

	void ensureCapacity();
};
*/
/*
Constructor default
Alocam loc pentru 5 elemente

template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT() :elems{ new Element[INITIAL_CAPACITY] }, cap{ INITIAL_CAPACITY }, lg{ 0 } {}

/*
Constructor de copiere
Obiectul current (this) acum se creaza
aloca spatiu pentru elemente
copieaza elementele din ot in this

template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT(const VectDinNewDeleteT<ElementT>& ot) {
	elems = new ElementT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
}

/*
Operator assgnment
elibereaza ce era in obiectul curent (this)
aloca spatiu pentru elemente
copieaza elementele din ot in this
 
template<typename ElementT>
VectDinNewDeleteT<ElementT>& VectDinNewDeleteT<ElementT>::operator=(const VectDinNewDeleteT<ElementT>& ot) {
	if (this == &ot) {
		return *this;//s-a facut l=l;
	}
	delete[] elems;
	elems = new ElementT[ot.cap];
	//copiez elementele
	for (int i = 0; i < ot.lg; i++) {
		elems[i] = ot.elems[i];  //assignment din Pet
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

/*
Eliberam memoria
 
template<typename ElementT>
VectDinNewDeleteT<ElementT>::~VectDinNewDeleteT() {
	delete[] elems;
}


/*
Move constructor
Apelat daca construim un nou vector dintr-un r-value (ex temporary)
Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
 
template<typename ElementT>
VectDinNewDeleteT<ElementT>::VectDinNewDeleteT(VectDinNewDeleteT&& ot) {
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
}

/*
Move assignment
Similar cu move constructor
Folosit la assignment
Elibereaza ce continea obiectul curent (this)
"fura" interiorul lui ot
pregateste ot pentru distrugere
 
template<typename ElementT>
VectDinNewDeleteT<ElementT>& VectDinNewDeleteT<ElementT>::operator=(VectDinNewDeleteT<ElementT>&& ot) {
	if (this == &ot) {
		return *this;
	}
	delete[] elems;
	// Copy the data pointer from other
	elems = ot.elems;
	lg = ot.lg;
	cap = ot.cap;

	// Release the data pointer from the source object so that  
	// the destructor does not free the memory multiple times.  
	ot.elems = nullptr;
	ot.lg = 0;
	ot.cap = 0;
	return *this;
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::add(const ElementT& el) {
	ensureCapacity();//daca e nevoie mai alocam memorie
	elems[lg++] = el;
}

template<typename ElementT>
ElementT& VectDinNewDeleteT<ElementT>::get(int poz) const {
	return elems[poz];
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::set(int poz, const ElementT& el) {
	elems[poz] = el;
}

template<typename ElementT>
int VectDinNewDeleteT<ElementT>::size() const noexcept {
	return lg;
}

template<typename ElementT>
void VectDinNewDeleteT<ElementT>::ensureCapacity() {
	if (lg < cap) {
		return; //mai avem loc
	}
	cap *= 2;
	ElementT* aux = new ElementT[cap];
	for (int i = 0; i < lg; i++) {
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
}

template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::begin()
{
	return IteratorVectorT<ElementT>(*this);
}

template<typename ElementT>
IteratorVectorT<ElementT> VectDinNewDeleteT<ElementT>::end()
{
	return IteratorVectorT<ElementT>(*this, lg);
}

template<typename ElementT>
class IteratorVectorT {
private:
	const VectDinNewDeleteT<ElementT>& v;
	int poz = 0;
public:
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept;
	IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept;
	bool valid()const;
	ElementT& element() const;
	void next();
	ElementT& operator*();
	IteratorVectorT& operator++();
	bool operator==(const IteratorVectorT& ot)noexcept;
	bool operator!=(const IteratorVectorT& ot)noexcept;
};

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v) noexcept :v{ v } {}

template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const VectDinNewDeleteT<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const {
	return v.elems[poz];
}

template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
	poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
	return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
	return !(*this == ot);
}

*/

template<typename ElemType>
class IteratorD;
template<typename ElemType>

class VectorD {
public:

	//constructorul implicit al vectorului dinamic
	VectorD();


	/*
	constructorul de copiere al vectorului dinamic
	date de intrare:
		ot - vector
	post: obiect de tip VectorD
	*/
	VectorD(const VectorD& ot);


	//desctructorul vectorului dinamic/ se elibereaza memoria
	~VectorD();


	/*
	rule 3
	operator de asignare
	elibereaza ce era in obiectul curent(this)
	aloca spatiu pentru elemente
	copiaza elementele din ot in this
		ot - vector dinamic
	*/
	VectorD& operator=(const VectorD& ot);

	/*
	Move constructor
	Apelat daca construim un nou vector dintr-un r-value
	Obiectul ot nu se mai foloseste astfel se poate refolosi interiorul lui
		ot - vector dinamic
	*/
	VectorD(VectorD&& ot);

	/*
	Move assignment
	Folosit la assignment
		ot - vector dinamic
	*/
	VectorD& operator=(VectorD&& ot);


	/*
	functie pentru adaugarea unui ElemType in vectorul dinamic
	date de intrare:
		el - ElemType-ul ce se doreste a fi adaugat
	post: el este adaugat in vectorul dinamic
	*/
	void add(const ElemType& el);

	/*
	functie pentru gasirea unui ElemType din vectorul dinamic de pe o anumita pozitie
	date de intrare:
		poz - pozitia ElemType-ului in vectorul dinamic
	post: se returneaza ElemType-ul
	*/
	ElemType& get(int poz) const noexcept;

	/*
	functie pentru setarea unui anumit ElemType la un alt ElemType
	date de intrare:
		el - ElemType-ul nou
		poz - pozitia ElemType-ului
	post: ElemType-ul de pe pozitia poz este inlocuit cu ElemType-ul el
	*/
	void set(int poz, const ElemType& el);


	/*
	functie pentru determinarea lungimii vectorului dinamic
	*/
	int len() const noexcept;


	/*
	functie pentru stergerea unui ElemType din vectorul dinamic
	date de intrare:
		denumire - denumirea ElemType-ului ce se doreste a fi sters
	post: ElemType-ul este sters din vectorul dinamic

	*/
	void del(int poz);


	friend class IteratorD<ElemType>;
	//functii care creeaza iteratori
	IteratorD<ElemType> begin() noexcept;
	IteratorD<ElemType> end() noexcept;

private:
	ElemType* elems;
	int lg; //numar elemente
	int capacity; //capacitate
	void ensureCapacity();
};

template<typename ElemType>
VectorD<ElemType>::VectorD()
	: elems{ new ElemType[5] }, capacity{ 5 }, lg{ 0 } {}


template<typename ElemType>
VectorD<ElemType>::VectorD(const VectorD<ElemType>& ot) {
	elems = new ElemType[ot.capacity];
	for (int i = 0; i < ot.lg; i++)
	{
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	capacity = ot.capacity;
}

template<typename ElemType>
VectorD<ElemType>::~VectorD() {
	delete[] elems;
}


template<typename ElemType>
VectorD<ElemType>& VectorD<ElemType>:: operator=(const VectorD<ElemType>& ot) {
	if (this == &ot)
	{
		return *this;
	}
	delete[] elems;
	elems = new ElemType[ot.capacity];
	for (int i = 0; i < ot.lg; i++)
	{
		elems[i] = ot.elems[i];
	}
	capacity = ot.capacity;
	lg = ot.lg;
	return *this;

}


template<typename ElemType>
VectorD<ElemType>::VectorD(VectorD<ElemType>&& ot)
{
	elems = ot.elems;
	lg = ot.lg;
	capacity = ot.capacity;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.capacity = 0;
}


template<typename ElemType>
VectorD<ElemType>& VectorD<ElemType>::operator=(VectorD<ElemType>&& ot) {
	if (this == &ot)
		return *this;

	delete[] elems;
	elems = ot.elems;
	lg = ot.lg;
	capacity = ot.capacity;

	ot.elems = nullptr;
	ot.lg = 0;
	ot.capacity = 0;
	return *this;
}



template<typename ElemType>
void VectorD<ElemType>::add(const ElemType& el) {
	if (capacity == lg)
	{
		ensureCapacity();
	}

	elems[lg] = el;
	lg++;
}

template<typename ElemType>
ElemType& VectorD<ElemType>::get(int poz) const noexcept {
	return elems[poz];
}

template<typename ElemType>
void VectorD<ElemType>::set(int poz, const ElemType& el) {
	elems[poz] = el;
}

template<typename ElemType>
void VectorD<ElemType>::del(int poz)
{
	for (int i = poz; i < lg - 1; i++)
	{
		ElemType& el = get(i + 1);
		set(i, el);
	}
	lg--;
}

template<typename ElemType>
int VectorD<ElemType>::len() const noexcept {
	return lg;
}


template<typename ElemType>
void VectorD<ElemType>::ensureCapacity()
{
	int const cap = capacity * 2;
	ElemType* aux = new ElemType[cap];
	for (int i = 0; i < lg; i++)
	{
		aux[i] = elems[i];
	}
	delete[] elems;
	elems = aux;
	capacity = capacity * 2;
}


template<typename ElemType>
IteratorD<ElemType> VectorD<ElemType>::begin() noexcept
{
	return IteratorD<ElemType>(*this, 0);
}


template<typename ElemType>
IteratorD<ElemType> VectorD<ElemType>::end() noexcept
{
	return IteratorD<ElemType>(*this, lg);
}


template<typename ElemType>
class IteratorD {

private:

	const VectorD<ElemType>& r;
	int poz = 0;

public:
	template<typename ElemType>
	/*
	functie pentru creeare iterator
	date de intrare
		r - vectorul dinamic cu elemente de tip ElemType
	post: obiect de tip IteratorD
	*/
	IteratorD(const VectorD<ElemType>& r) noexcept : r{ r } {};


	/*
	functie pentru creeare iterator
	date de intrare
		r - vectorul dinamic cu elemente de tip ElemType
		poz - pozitie
	post: obiect de tip IteratorD
	*/
	IteratorD(const VectorD<ElemType>& r, int poz) noexcept :
		r{ r }, poz{ poz } {};


	/*
	functie pentru verificarea validitatii iteratorului
	returneaza true daca este valid
			   fals, altfel
	*/
	bool valid() const;


	/*
	functie pentru obtinerea unui element de tip ElemType, cu ajutorul iteratorului
	returneaza elementul curent
	*/
	ElemType& element() const noexcept;


	/*
	functie pentru trecerea pe pozitia urmatoare
	*/
	void next() noexcept;

	//Suprascriere operator *
	ElemType& operator*() noexcept; //elems

	//Suprascriere operator ++
	IteratorD& operator++() noexcept; //next

	//Suprascriere operator ==
	bool operator==(const IteratorD& ot) noexcept;

	//Suprascriere operator !=
	bool operator!=(const IteratorD& ot) noexcept;

};


template<typename ElemType>
bool IteratorD<ElemType>::valid() const
{
	return poz < r.lg;
}


template<typename ElemType>
ElemType& IteratorD<ElemType>::element() const noexcept
{
	return r.elems[poz];
}


template<typename ElemType>
void IteratorD<ElemType>::next() noexcept {
	poz++;
}

template<typename ElemType>
ElemType& IteratorD<ElemType>::operator*() noexcept {
	return element();
}

template<typename ElemType>
IteratorD<ElemType>& IteratorD<ElemType>::operator++() noexcept {
	next();
	return *this;
}


template<typename ElemType>
bool IteratorD<ElemType>::operator==(const IteratorD<ElemType>& ot) noexcept {
	return poz == ot.poz;
}

template<typename ElemType>
bool IteratorD<ElemType>::operator!=(const IteratorD<ElemType>& ot) noexcept {
	return !(*this == ot);
}


