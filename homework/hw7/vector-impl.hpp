#define VECTOR_MINIMUM_CAPACITY     2   // Minimun capacity for a vector 
#define VECTOR_GROWTH_FACTOR        2   // When vector is full, gain its capacity to VECTOR_GROWTH_FACTOR*original_capacity

namespace __detail
{
    // Iterator of vector 
    template <typename _Tp>
    class __iterator{
    public:
        _Tp* pointer;
        __iterator(){ pointer = NULL; }                                 // Default constructor
        __iterator(const __iterator& other){ pointer = other.pointer; } // Copy constructor
        __iterator(_Tp * ptr){ pointer = ptr; }                         // Initialize the iterator with a pointer
        ~__iterator(){}                                                 // Destructor

        // copy assignment operator
        __iterator<_Tp>& operator =(const __iterator<_Tp>& x){
            this->pointer = x.pointer;
            return *this;
        }

        // dereference operator
        _Tp& operator *(){
            return *(this->pointer);
        }

        // arrow operator
        _Tp* operator ->(){
            return this->pointer;
        }

        // comparison operator ==
        bool operator ==(const __iterator<_Tp>& other){
            return this->pointer == other.pointer;
        }

        // comparison operator !=
        bool operator !=(const __iterator<_Tp>& other){
            return this->pointer != other.pointer;
        }

        // self increment operator
        __iterator<_Tp>& operator ++(){
            this->pointer++;
            return *this;
        } 

        // self increment operator
        __iterator<_Tp> operator ++(int){
            __iterator<_Tp> tmp = *this;
            this->pointer++;
            return tmp;
        }

        // self decrement operator
        __iterator<_Tp>& operator --(){
            this->pointer--;
            return *this;
        }

        // self decrement operator
        __iterator<_Tp> operator --(int){
            __iterator<_Tp> tmp = *this;
            this->pointer--;
            return tmp;
        }

        // arithmetic operator +
        __iterator<_Tp> operator +(int n){
            __iterator<_Tp> tmp = *this;
            tmp.pointer += n;
            return tmp;
        }

        // arithmetic operator -
        __iterator<_Tp> operator -(int n){
            __iterator<_Tp> tmp = *this;
            tmp.pointer -= n;
            return tmp;
        }

        // compound assignment operator +=
        __iterator<_Tp>& operator +=(int n){
            this->pointer += n;
            return *this;
        }

        // compound assignment operator -=
        __iterator<_Tp>& operator -=(int n){
            this->pointer -= n;
            return *this;
        }
    };

    // Const iterator of vector 
    template <typename _Tp>
    class __const_iterator{
    public:
        _Tp* pointer;
        __const_iterator(){ pointer = NULL; }                                             // Default constructor
        __const_iterator(const __const_iterator& other){ pointer = other.pointer; } // Copy constructor
        __const_iterator(_Tp* ptr){ pointer = ptr; }                                      // Initialize the iterator with a pointer
        __const_iterator(const __iterator<_Tp>& other){ pointer = other.pointer; }       // Convert an iterator into a const iterator
        ~__const_iterator(){}                                                             // Destructor

        // copy assignment operator
        __const_iterator<_Tp>& operator =(const __const_iterator<_Tp> &x){
            this->pointer = x.pointer;
            return *this;
        }

        // dereference operator
        const _Tp& operator *() const{
            return *(this->pointer);
        }

        // arrow operator
        _Tp* operator ->(){
            return this->pointer;
        }

        // comparison operator ==
        bool operator ==(const __const_iterator<_Tp>& other){
            return this->pointer == other.pointer;
        }

        // comparison operator !=
        bool operator !=(const __const_iterator<_Tp>& other){
            return this->pointer != other.pointer;
        }

        // self increment operator
        __const_iterator<_Tp>& operator ++(){
            this->pointer++;
            return *this;
        } 

        // self increment operator
        __const_iterator<_Tp> operator ++(int){
            __const_iterator<_Tp> tmp = *this;
            this->pointer++;
            return tmp;
        }

        // self decrement operator
        __const_iterator<_Tp>& operator --(){
            this->pointer--;
            return *this;
        }

        // self decrement operator
        __const_iterator<_Tp> operator --(int){
            __const_iterator<_Tp> tmp = *this;
            this->pointer--;
            return tmp;
        }

        // arithmetic operator +
        __const_iterator<_Tp> operator +(int n){
            __const_iterator<_Tp> tmp = *this;
            tmp.pointer += n;
            return tmp;
        }

        // arithmetic operator -
        __const_iterator<_Tp> operator -(int n){
            __const_iterator<_Tp> tmp = *this;
            tmp.pointer -= n;
            return tmp;
        }

        // compound assignment operator +=
        __const_iterator<_Tp>& operator +=(int n){
            this->pointer += n;
            return *this;
        }

        // compound assignment operator -=
        __const_iterator<_Tp>& operator -=(int n){
            this->pointer -= n;
            return *this;
        }
    };
}

// Default constructor
template <typename _Tp>
vector<_Tp>::vector(){
    _M_size = 0;
    _M_capacity = VECTOR_MINIMUM_CAPACITY;
    _M_data = new _Tp[VECTOR_MINIMUM_CAPACITY];
}

// Create a vector with $size copies of $value
template <typename _Tp>
vector<_Tp>::vector(size_type size, const _Tp &value){
    _M_size = size;
    _M_capacity = (size > VECTOR_MINIMUM_CAPACITY) ? size : VECTOR_MINIMUM_CAPACITY;
    _M_data = new _Tp[size];
    for (size_type i = 0; i < size; i++)    // initialize
        _M_data[i] = value;
}

// Create a vector consists of the elements in the initializer_list
template <typename _Tp>
vector<_Tp>::vector(std::initializer_list<_Tp> l){
    _M_size = l.size();
    _M_capacity = (l.size() > VECTOR_MINIMUM_CAPACITY) ? l.size() : VECTOR_MINIMUM_CAPACITY;
    _M_data = new _Tp[l.size()];
    size_type index = 0;
    for (_Tp t:l){  // initialize
        _M_data[index] = t;
        ++index;
    }
}

// Destructor
template <typename _Tp>
vector<_Tp>::~vector(){
    delete[] _M_data;   // free memory
}

// Subscript access to the data contains in the vector
template <typename _Tp>
_Tp& vector<_Tp>::operator[](size_type n){
    return _M_data[n];
}

// The size of the vector
template <typename _Tp>
typename vector<_Tp>::size_type vector<_Tp>::size() const{
    return _M_size;
}

// Iterator begin()
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::begin(){
    iterator iter = _M_data;
    return iter;
}

// Iterator end()
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::end(){
    iterator iter = _M_data + _M_size;
    return iter;
}

// Const iterator cbegin()
template <typename _Tp>
typename vector<_Tp>::const_iterator vector<_Tp>::cbegin() const{
    const_iterator iter = _M_data;
    return iter;
}

// Const iterator cend()
template <typename _Tp>
typename vector<_Tp>::const_iterator vector<_Tp>::cend() const{
    const_iterator iter = _M_data + _M_size;
    return iter;
}

// Insert given value into vector before specified iterator
// Return an iterator that points to the inserted data
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::insert(iterator pos, const _Tp &value){
    int index = pos.pointer - this->begin().pointer;
    if (_M_size + 1 > _M_capacity)  _grow();
    pos.pointer = this->begin().pointer + index;
    for (iterator it = this->end(); it.pointer > pos.pointer; --it)
        *it = *(it - 1);
    *pos = value;
    _M_size++;
    return pos;
}

// Insert given value into vector before specified const iterator
// Return an iterator that points to the inserted data
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::insert(const_iterator pos, const _Tp &value){
    int index = pos.pointer - this->begin().pointer;
    if (_M_size + 1 > _M_capacity)  _grow();
    iterator tmp(this->begin().pointer + index);
    for (iterator it = this->end(); it.pointer > tmp.pointer; --it)
        *it = *(it - 1);
    *tmp = value;
    _M_size++;
    return tmp;
}

// Add data to the end of the vector
template <typename _Tp>
void vector<_Tp>::push_back(const _Tp &value){
    if (_M_size + 1 > _M_capacity)  _grow();
    _M_data[_M_size] = value;
    _M_size++;
}

// Remove element at given position
// Return an iterator to the next element (or end())
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::erase(iterator pos){
    for (iterator it = pos + 1; it.pointer < this->end().pointer; ++it)
        *(it - 1) = *it;
    _M_size--;
    return pos;
}

// Remove element at given position
// Return an iterator to the next element (or end())
template <typename _Tp>
typename vector<_Tp>::iterator vector<_Tp>::erase(const_iterator pos){
    iterator tmp(pos.pointer);
    for (iterator it = tmp + 1; it.pointer < this->end().pointer; ++it)
        *(it - 1) = *it;
    _M_size--;
    return tmp;
}

// Remove last element
template <typename _Tp>
void vector<_Tp>::pop_back(){
    _M_size--;
}

// grow vector to size of capacity
template <typename _Tp>
void vector<_Tp>::_grow(){
    _M_capacity *= VECTOR_GROWTH_FACTOR;
    pointer tmp = new _Tp[_M_size];
    for (size_type i = 0; i < _M_size; i++)    // copy _M_data
        tmp[i] = _M_data[i];
    delete[] _M_data;
    _M_data = new _Tp[_M_capacity];
    for (size_type i = 0; i < _M_size; i++)    // initialize
        _M_data[i] = tmp[i];
    delete[] tmp;
}