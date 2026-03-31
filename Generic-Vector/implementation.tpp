#include "vector.h"
#include <iostream>

// Ctors and Dtor
template <typename T>
Vector<T>::Vector() {
	this->m_capacity = 1;
	this->m_size = 0;
	this->m_data = new T[1];

	if (m_data == nullptr) {
		throw std::bad_alloc();
	}
}

template <typename T>
Vector<T>::Vector(const Vector &other) {
	if ((this->m_data) == (other.m_data)) {
		this->m_data = other.m_data;	
	} else {
		this->m_capacity = other.m_capacity;
		this->m_size = other.m_size;
		this->m_data = new T[other.m_capacity];

		for (size_t i = 0; i < m_size; ++i) {
			this->m_data[i] = other.m_data[i];
		}
	}
}

template <typename T>
Vector<T>::Vector(Vector &&other) {
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_data = other.m_data;
	other.m_data = nullptr;

}

template <typename T>
Vector<T>::~Vector() {
	delete[] m_data;
	m_data = nullptr;
}

// Functionality
template <typename T>
void Vector<T>::resize(size_t new_cap) {
	if (m_data == nullptr) {
		return;
	}

	int *tmp_space = new int[new_cap];

	if (tmp_space == nullptr) {
		std::cout << "Allocation failed" << std::endl;
		return;
	}

	for (int i = 0; i < m_size; ++i) {
		tmp_space[i] = m_data[i];
	}

	delete[] m_data;
	m_data = tmp_space;
}

template <typename T>
void Vector<T>::push_back(T value) {
	if (m_size == m_capacity) {
		m_capacity *= 2;
		this->resize(m_capacity);
	}
	
	m_data[m_size++] = value;
}

template <typename T>
void Vector<T>::push_front(T value) {
	if (m_size == m_capacity) {
		m_capacity *= 2;
		this->resize(m_capacity);
	}
	
	for (size_t i = m_size; i > 0; --i) {
		m_data[i] = m_data[i - 1];
	}

	m_data[0] = value;
	++m_size;
}
template <typename T>

T Vector<T>::at(size_t pos) {
	if (pos >= m_size) {
		throw std::out_of_range();
	}

	return m_data[pos];
}

template <typename T>
size_t Vector<T>::get_size(void) const {
	return m_size;
}

template <typename T>
size_t Vector<T>::get_capacity(void) const {
	return m_capacity;
}

template <typename T>
bool Vector<T>::is_empty(void) const {
	return (m_size == 0) ? true : false;
}

template <typename T>
T Vector<T>::front(void) const {
	return m_data[0];
}

template <typename T>
T Vector<T>::back(void) const {
	if (this->is_empty() == true) {
		std::cout << "Vector is empty" << std::endl;
		return -1;
	}

	return m_data[m_size - 1];
}

template <typename T>
void Vector<T>::shrink_to_fit(void) {
	if (this->is_empty() == true) {
		return;
	}

	m_capacity = m_size;
	this->resize(m_size);
}

template <typename T>
void Vector<T>::insert(size_t index, T value) {
	if (index > m_size) {
		return;
	}
	
	if (m_capacity == m_size) {
		m_capacity *= 2;
		resize(m_capacity);
	}

	if (index == 0) {
		this->push_front(value);
		return;
	}

	if (index == m_size - 1) {
		this->push_back(value);
		return;
	}

	for (size_t i = m_size; i > index; --i) {
		m_data[i] = m_data[i - 1];
	}

	m_data[index] = value;
	++m_size;
}

template <typename T>
void Vector<T>::erase(size_t index) {
	if (index >= m_size) {
		return;
	}

	for (size_t i = index; i < m_size - 1; ++i) {
		m_data[i] = m_data[i + 1];
	}

	--m_size;
}

template <typename T>
void Vector<T>::clear(void) {
	m_size = 0;
}

template <typename T>
void Vector<T>::list_vector(void) const {
	for (size_t i = 0; i < m_size; ++i) {
		std::cout << m_data[i] << std::endl;
	}
}

template <typename T>
bool Vector<T>::operator==(const Vector &rhs) {
	if (this == &rhs) {
		return true;
	}
	
	if (this->m_capacity != rhs.m_capacity) {
		return false;
	}

	if (this->m_size != rhs.m_size) {
		return false;
	}

	for (size_t i = 0; i < this->m_size; ++i) {
		if (this->m_data[i] != rhs.m_data[i]) {
			return false;
		}
	}

	return true;
}

// template <typename T>
// Vector<T>::const_iterator::const_iterator(const T *in_iter) : citer::m_iter{in_iter} {}

// template <typename T>
// Vector<T>::const_iterator::pointer Vector<T>::const_iterator::base() const { return citer::m_iter; }

// template <typename T>
// Vector<T>::const_iterator::reference Vector<T>::const_iterator::operator*() const { return *this; }

// template <typename T>
// Vector<T>::const_iterator::pointer Vector<T>::const_iterator::operator->() const { return this; }

// template <typename T>
// typename Vector<T>::const_iterator::value_type Vector<T>::const_iterator::operator[](size_t n) const {
// 	if (n >= m_iter.size()) {
// 		throw std::out_of_range();
// 	}

// 	return m_iter[n];
// }

// template <typename T>
// typename Vector<T>::const_iterator &Vector<T>::const_iterator::operator++() { 
// 	++m_iter;
// 	return *this;
//  }

// // template <typename T>
// // Vector<T>::const_iterator Citer::operator++(int) { 
// // 	const_iterator citer
// // }