#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>

template <typename T>
class Vector {
	private:
		size_t m_capacity;
		size_t m_size;
		T *m_data;
	public:
		Vector();
		Vector(const Vector &other);
		Vector(Vector &&other);
		~Vector();

		void push_back(T value);
		void push_front(T value);
		T at(size_t index);
		size_t get_size(void) const;
		size_t get_capacity(void) const;
		void resize(size_t new_cap);
		T front(void) const;
		T back(void) const;
		bool is_empty(void) const;
		void shrink_to_fit(void);
		void insert(size_t index, T value);
		void erase(size_t index);
		void clear(void);
		void list_vector(void) const;
		bool operator==(const Vector &rhs);
		
		// Constant Iterator
		class const_iterator {
			private:
			const T *m_citer;
			public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const T;
			using difference_type = std::ptrdiff_t;
			using reference = const T&;
			using pointer = const T*;
			
			explicit const_iterator(const T *citer) : m_citer{citer} {}			
			
			pointer base() const { return m_citer; }
			reference operator*() const { return *m_citer; }
			pointer operator->() const { return m_citer; };
			value_type operator[](difference_type n) const { return m_citer[n]; };
			const_iterator &operator++() const {
				++m_citer;
				return *this;
			}
			const_iterator operator++(int) const {
				const_iterator tmp_citer(m_citer);
				++m_citer;
				return tmp_citer;
			}
			const_iterator &operator--() const {
				--m_citer;
				return *this;
			}
			const_iterator operator--(int) const {
				const_iterator tmp_citer(m_citer);
				--m_citer;
				return tmp_citer;
			}
			const_iterator &operator+=(difference_type n) const {
				m_citer += n;
				return *this;
			}
			const_iterator &operator-=(difference_type n) const {
				m_citer -= n;
				return *this;
			}
			
			constexpr bool operator==(const const_iterator &rhs) const { return m_citer == rhs.m_citer; }
			constexpr bool operator<(const const_iterator &rhs) const { return m_citer < rhs.m_citer; }
			constexpr bool operator>(const const_iterator &rhs) const { return m_citer > rhs.m_citer; }
			constexpr bool operator<=(const const_iterator &rhs) const { return m_citer <= rhs.m_citer; }
			constexpr bool operator>=(const const_iterator &rhs) const { return m_citer >= rhs.m_citer; }
			constexpr bool operator!=(const const_iterator &rhs) const { return !(m_citer == rhs.m_citer); }
			
			friend bool operator<(const const_iterator &lhs, const const_iterator &rhs) { return lhs.m_citer < rhs.m_citer; }
			friend bool operator>(const const_iterator &lhs, const const_iterator &rhs) { return lhs.m_citer > rhs.m_citer; }
			friend bool operator<=(const const_iterator &lhs, const const_iterator &rhs) { return lhs.m_citer <= rhs.m_citer; }
			friend bool operator>=(const const_iterator &lhs, const const_iterator &rhs) { return lhs.m_citer >= rhs.m_citer; }
			
			friend const_iterator operator-(const const_iterator &iter, difference_type n) { return const_iterator(iter.base() - n); }
			friend const_iterator operator-(difference_type n, const const_iterator &iter) { return const_iterator(iter.base() - n); }
			friend const_iterator operator+(const const_iterator &iter, difference_type n) { return const_iterator(iter.base() + n); }
			friend const_iterator operator+(difference_type n, const const_iterator &iter) { return const_iterator(iter.base() + n); }
			
		};
		
		// Iterator
		class iterator {
			private:
				T *m_iter;
			public:
				using iterator_category = std::random_access_iterator_tag;
				using value_type = T;
				using difference_type = std::ptrdiff_t;
				using reference = T&;
				using pointer = T*;

				explicit iterator(T *iter) : m_iter{iter} {}

				pointer base() const { return m_iter; }
				reference operator*() const { return *m_iter; }
				pointer operator->() const { return m_iter; }
				value_type operator[](difference_type n) const { return m_iter[n]; }
				iterator &operator++() {
					++m_iter;
					return *this;
				}
				iterator operator++(int) {
					iterator tmp_iter(m_iter);
					++m_iter;
					return tmp_iter;
				}
				iterator &operator--() {
					--m_iter;
					return *this;
				}
				iterator operator--(int) {
					iterator tmp_iter(m_iter);
					--m_iter;
					return tmp_iter;
				}
				iterator &operator+=(difference_type n) {
					m_iter += n;
					return *this;
				}
				iterator &operator-=(difference_type n) {
					m_iter -= n;
					return *this;
				}

				constexpr bool operator==(const iterator &rhs) { return m_iter == rhs.m_iter; }
				constexpr bool operator<(const iterator &rhs) { return m_iter < rhs.m_iter; }
				constexpr bool operator>(const iterator &rhs) { return m_iter > rhs.m_iter; }
				constexpr bool operator<=(const iterator &rhs) { return m_iter <= rhs.m_iter; }
				constexpr bool operator>=(const iterator &rhs) { return m_iter >= rhs.m_iter; }
				constexpr bool operator!=(const iterator &rhs) const { return !(m_iter == rhs.m_iter); }

				friend bool operator<(const iterator &lhs, const iterator &rhs) { return lhs.m_iter < rhs.m_iter; }
				friend bool operator>(const iterator &lhs, const iterator &rhs) { return lhs.m_iter > rhs.m_iter; }
			    friend bool operator<=(const iterator &lhs, const iterator &rhs) { return lhs.m_iter <= rhs.m_iter; }
				friend bool operator>=(const iterator &lhs, const iterator &rhs) { return lhs.m_iter >= rhs.m_iter; }

				friend difference_type operator-(const iterator &lhs, const iterator &rhs) { return lhs.m_iter - rhs.m_iter; }
				friend iterator operator-(const iterator &iter, difference_type n) { return iterator(iter.base() - n); }
				friend iterator operator-(difference_type n, const iterator &iter) { return iterator(iter.base() - n); }
				friend iterator operator+(const iterator &iter, difference_type n) { return iterator(iter.base() + n); }
				friend iterator operator+(difference_type n, const iterator &iter) { return iterator(iter.base() + n); }
		};
		
		// Reverse Iterator
		template <class Iter>
		class reverse_iterator {
			private:
				Iter m_current;
			public:
				using iterator_category = std::random_access_iterator_tag;
				using iterator_type = Iter;
				using difference_type = std::ptrdiff_t;
				using reference = typename std::iterator_traits<Iter>::reference;
				using pointer = typename std::iterator_traits<Iter>::pointer;

				reverse_iterator() = default;
				explicit reverse_iterator(Iter riter) : m_current{riter} {}

				template <class U>
				reverse_iterator(const reverse_iterator<U> &other) : m_current{other.m_current} {}

				reverse_iterator& operator=(const reverse_iterator &other) {
					m_current = other.m_current;
					return *this;
				}

				iterator_type base() const { return m_current; }
				reference operator*() const {
					Iter tmp_iter{m_current};
					--tmp_iter;
					return *tmp_iter;
				}
				pointer operator->() const { 
					Iter tmp_riter{m_current};
					--tmp_riter;
					return tmp_riter.operator->(); 
				}
				reference operator[](difference_type n) {
					return m_current[-n - 1];
				}
				reverse_iterator &operator++() { 
					--m_current;
					return *this; 
				}
				reverse_iterator operator++(int) {
					reverse_iterator tmp_riter{m_current};
					--m_current;
					return tmp_riter;
				}
				reverse_iterator &operator--() { 
					++m_current;
					return *this; 
				}
				reverse_iterator operator--(int) {
					reverse_iterator tmp_riter{m_current};
					++m_current;
					return tmp_riter;
				}
					
				reverse_iterator operator+(difference_type n) { return reverse_iterator{m_current - n}; }
				reverse_iterator &operator+=(difference_type n) {
					m_current -= n;
					return *this;
				}
				reverse_iterator operator-(difference_type n) { return reverse_iterator{m_current + n}; }
				reverse_iterator &operator-=(difference_type n) {
					m_current += n;
					return *this;
				}

				template <typename Iter1, typename Iter2>
				friend bool operator==(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return lhs.base() == rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator!=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return !(lhs.base() == rhs.base()); }
				template <typename Iter1, typename Iter2>
				friend bool operator<(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return lhs.base() < rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator>(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return lhs.base() > rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator<=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return lhs.base() <= rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator>=(const reverse_iterator<Iter1> &lhs, const reverse_iterator<Iter2> &rhs) { return lhs.base() >= rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend difference_type operator-(const Iter1 &lhs, const Iter2 &rhs) { return lhs.base() - rhs.base(); }
		};
		
		// Constant Reverse Iterator
		template <class CRIter>
		class const_reverse_iterator {
			private:
				mutable CRIter m_current;
			public:
				using iterator_category = std::random_access_iterator_tag;
				using iterator_type = const CRIter;
				using difference_type = std::ptrdiff_t;
				using reference = typename std::iterator_traits<CRIter>::reference;
				using pointer = typename std::iterator_traits<CRIter>::pointer;

				// const_reverse_iterator() = default;
				explicit const_reverse_iterator(const CRIter &riter) : m_current{riter} {}

				template <class U>
				const_reverse_iterator(const const_reverse_iterator<U> &other) : m_current{other.m_current} {}

				iterator_type base() const { return m_current; }
				reference operator*() const {
					CRIter tmp_iter{m_current};
					--tmp_iter;
					return *tmp_iter;
				}
				pointer operator->() const { 
					CRIter tmp_riter{m_current};
					--tmp_riter;
					return tmp_riter.operator->(); 
				}
				reference operator[](difference_type n) const {
					return m_current[-n - 1];
				}
				const_reverse_iterator &operator++() { 
					--m_current;
					return *this; 
				}
				const_reverse_iterator operator++(int) {
					const_reverse_iterator tmp_riter{m_current};
					--m_current;
					return tmp_riter;
				}
				const_reverse_iterator &operator--() const { 
					++m_current;
					return *this; 
				}
				const_reverse_iterator operator--(int) const {
					const_reverse_iterator tmp_riter{m_current};
					++m_current;
					return tmp_riter;
				}
					
				const_reverse_iterator operator+(difference_type n) const { return const_reverse_iterator{m_current - n}; }
				const_reverse_iterator &operator+=(difference_type n) const {
					m_current -= n;
					return *this;
				}
				const_reverse_iterator operator-(difference_type n) const { return const_reverse_iterator{m_current + n}; }
				const_reverse_iterator &operator-=(difference_type n) const {
					m_current += n;
					return *this;
				}

				template <typename Iter1, typename Iter2>
				friend bool operator==(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return lhs.base() == rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator!=(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return !(lhs.base() == rhs.base()); }
				template <typename Iter1, typename Iter2>
				friend bool operator<(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return lhs.base() < rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator>(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return lhs.base() > rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator<=(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return lhs.base() <= rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend bool operator>=(const const_reverse_iterator<Iter1> &lhs, const const_reverse_iterator<Iter2> &rhs) { return lhs.base() >= rhs.base(); }
				template <typename Iter1, typename Iter2>
				friend difference_type operator-(const Iter1 &lhs, const Iter2 &rhs) { return lhs.base() - rhs.base(); }
		};

		inline const_iterator cbegin() { return const_iterator(m_data); }
		inline const_iterator cend() { return const_iterator(m_data + m_size); }
		inline iterator begin() { return iterator(m_data); }
		inline iterator end() { return iterator(m_data + m_size); }
		inline reverse_iterator<T*> rbegin() { return reverse_iterator<T*>(m_data + m_size); }
		inline reverse_iterator<T*> rend() { return reverse_iterator<T*>(m_data); }
		inline const_reverse_iterator<const T*> crbegin() { return const_reverse_iterator<const T*>{m_data + m_size}; }
		inline const_reverse_iterator<const T*> crend() { return const_reverse_iterator<const T*>{m_data}; }
};

#include "implementation.tpp"
#endif