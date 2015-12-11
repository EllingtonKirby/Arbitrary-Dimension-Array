#ifndef XXX_ARRAY_XXX
#define XXX_ARRAY_XXX
#include <type_traits>
#include <stddef.h>

/*QUESTIONS:
 * 	How to go from 2nd to last iterator case to A<T, Dim> iterator? enable_if?
 */


namespace cs540{

	struct OutOfRange {};

	template<typename T, size_t... Dims>
	class Array;
	
	/*
	* Using constexpr.   
	*/

	template <typename T>
	constexpr int calcProduct(const T &v) {
		return v;
	}

	template <typename T, typename... Ts>
	constexpr int calcProduct(const T &v, const Ts &... params) {
		return v * calcProduct(params...);
	}
	
	template<typename T, size_t Dim>
		class Array<T, Dim>{
			public:
				typedef T ValueType;
				T container[Dim];
				
				Array(){
					static_assert(Dim, "Container cannot have dimension with size 0");	
				};

				Array(const Array& A) {
					static_assert(Dim, "Container cannot have dimension with size 0");	
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				template<typename U>
				Array(const Array<U, Dim> &A){
					static_assert(Dim, "Container cannot have dimension with size 0");	
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				Array& operator=(const Array &A){
					if(this == &A){
						return *this;
					}
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				};

				template<typename U>
				Array& operator=(const Array<U, Dim> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				}

				T& operator[](int index){
					if(index < Dim && index >= 0){
						return container[index];
					}
					else{
						throw OutOfRange();
					}
				};

				const T& operator[](int index) const{
					if(index < Dim && index >= 0){
						return container[index];
					}
					else{
						throw OutOfRange();
					}
				};

				template<size_t D>
				class Indexer{
					public:
						Indexer() : m_index(0){};

						void setValue(){
							m_index = D - 1;
						};

						bool fdm_inc() {
							if(++m_index == D){
								return true;
							}
							return false;
						};

						void ldm_inc(){
							m_index++;
						};

						friend bool operator==(const Indexer<D> &lhs, const Indexer<D> &rhs){
							return lhs.m_index == rhs.m_index;
						};

						size_t m_index;
				};
 
				class FirstDimensionMajorIterator{
					public:
						Indexer<Dim> indexer;
						Array<T, Dim> *parent;

						FirstDimensionMajorIterator();

						FirstDimensionMajorIterator(Indexer<Dim> i, Array<T, Dim> *p) : indexer(i), parent(p) {};

						FirstDimensionMajorIterator& operator++(){
							indexer.fdm_inc();
							return *this;	
						};

						FirstDimensionMajorIterator operator++(int){
							auto temp = *this;
							indexer.fdm_inc();
							return temp;	
						};

						T& operator*() const{
							return parent->container[indexer.m_index];
						};

						friend bool operator==(const FirstDimensionMajorIterator &lhs, const FirstDimensionMajorIterator &rhs){
							return lhs.indexer == rhs.indexer;
						};

						friend bool operator!=(const FirstDimensionMajorIterator &lhs, const FirstDimensionMajorIterator &rhs){
							return !(lhs.indexer == rhs.indexer);
						};
				};

				class LastDimensionMajorIterator{
					public:
						Indexer<Dim> indexer;
						Array<T, Dim> *parent;

						LastDimensionMajorIterator();

						LastDimensionMajorIterator(Indexer<Dim> i, Array<T, Dim> *p) : indexer(i), parent(p) {};
			
						LastDimensionMajorIterator& operator++(){
							indexer.ldm_inc();
							return *this;
						};

						LastDimensionMajorIterator operator++(int){
							auto temp = *this;
							indexer.ldm_inc();
							return temp;
						};

						T& operator*() const{
							return parent->container[indexer.m_index];
						};

						friend bool operator==(const LastDimensionMajorIterator &lhs, const LastDimensionMajorIterator &rhs){
							return lhs.indexer == rhs.indexer;
						};

						friend bool operator!=(const LastDimensionMajorIterator &lhs, const LastDimensionMajorIterator &rhs){
							return !(lhs.indexer == rhs.indexer);
						};
				};

				
				FirstDimensionMajorIterator fmbegin(){
					Indexer<Dim> i;
					return FirstDimensionMajorIterator(i, this);
				};

				FirstDimensionMajorIterator fmend(){
					Indexer<Dim> i; 
					i.setValue();
					i.fdm_inc();
					return FirstDimensionMajorIterator(i, this);
				};

				LastDimensionMajorIterator lmbegin(){
					Indexer<Dim> i;
					return LastDimensionMajorIterator(i, this);
				};

				LastDimensionMajorIterator lmend(){
					Indexer<Dim> i;
					i.setValue();
					i.ldm_inc();
					return LastDimensionMajorIterator(i, this);
				};
		};

	template<typename T, size_t Dim, size_t... Dims>
		class Array<T, Dim, Dims...>{
			public:
				typedef T ValueType;
				Array<T, Dims...> container[Dim];
			
				Array(){
					static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");	
				};

				Array(const Array& A){
					static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");		
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				template<typename U>
				Array(const Array<U, Dim, Dims...> &A){
					static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");	
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				Array& operator=(const Array &A){
					if(this == &A){
						return *this;
					}
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				};

				template<typename U>
				Array& operator=(const Array<U, Dim, Dims...> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				}

				Array<T, Dims...>& operator[](int index){
					if(index < Dim && index >= 0){
						return container[index];
					}
					else{
						throw OutOfRange();
					}
				};

				const Array<T, Dims...>& operator[](int index) const {
					if(index < Dim && index >= 0){
						return container[index];
					}
					else{
						throw OutOfRange();
					}
				};

				template<size_t D, size_t... Ds>
				class Indexer{
					public:
						Indexer() : m_index(0){};

						void setValue(){
							m_index = D - 1;
							m_nested.setValue();
						};

						bool fdm_inc(){
							if(m_nested.fdm_inc()){
								m_nested.m_index = 0;
								if(++m_index == D){
									return true;
								}	
							}	
							return false;
						};

						void ldm_inc(){
							if(++m_index == D){
								m_index = 0;
								m_nested.ldm_inc();
							}
						};

						friend bool operator==(const Indexer<D, Ds...> &lhs, const Indexer<D, Ds...> &rhs){
							if(lhs.m_index == rhs.m_index){
								return lhs.m_nested == rhs.m_nested;
							}
							return false;
						};

						size_t m_index;
						typename Array<T, Ds...>::template Indexer<Ds...> m_nested;
				};
						
				class FirstDimensionMajorIterator{
					public:
						Indexer<Dim, Dims...> indexer;
						Array<T, Dim, Dims...> *parent;

						FirstDimensionMajorIterator();

						FirstDimensionMajorIterator(Array<T, Dim, Dims...>::Indexer<Dim, Dims...> i, Array<T, Dim, Dims...> *p) : indexer(i), parent(p) {};

						FirstDimensionMajorIterator& operator++(){
							indexer.fdm_inc();
							return *this;	
						};

						FirstDimensionMajorIterator operator++(int){
							auto temp = *this;
							indexer.fdm_inc();
							return temp;	
						};

						T& operator*() const{
							Array<T, Dims...> *p = &parent->container[indexer.m_index];
							typename Array<T, Dims...>::FirstDimensionMajorIterator temp(indexer.m_nested, p);
							return *temp;
						};

						friend bool operator==(const FirstDimensionMajorIterator &lhs, const FirstDimensionMajorIterator &rhs){
							return lhs.indexer == rhs.indexer;
						};

						friend bool operator!=(const FirstDimensionMajorIterator &lhs, const FirstDimensionMajorIterator &rhs){
							return !(lhs.indexer == rhs.indexer);
						};
				};

				class LastDimensionMajorIterator{
					public:
						Indexer<Dim, Dims...> indexer;
						Array<T, Dim, Dims...> *parent;

						LastDimensionMajorIterator();

						LastDimensionMajorIterator(Array<T, Dim, Dims...>::Indexer<Dim, Dims...> i, Array<T, Dim, Dims...> *p) : indexer(i), parent(p) {};

						LastDimensionMajorIterator& operator++(){
							indexer.ldm_inc();
							return *this;
						};

						LastDimensionMajorIterator operator++(int){
							auto temp = *this;
							indexer.ldm_inc();
							return temp;
						};

						T& operator*() const{
							Array<T, Dims...> *p = &parent->container[indexer.m_index];
							typename Array<T, Dims...>::LastDimensionMajorIterator temp(indexer.m_nested, p);
							return *temp;
						};

						friend bool operator==(const LastDimensionMajorIterator &lhs, const LastDimensionMajorIterator &rhs){
							return lhs.indexer == rhs.indexer;
						};

						friend bool operator!=(const LastDimensionMajorIterator &lhs, const LastDimensionMajorIterator &rhs){
							return !(lhs.indexer == rhs.indexer);
						};
				};


				FirstDimensionMajorIterator fmbegin(){
					Indexer<Dim, Dims...> i;
					return FirstDimensionMajorIterator(i, this);
				};

				FirstDimensionMajorIterator fmend(){
					Indexer<Dim, Dims...> i;
					i.setValue();
					i.fdm_inc();
					return FirstDimensionMajorIterator(i, this);
				};

				LastDimensionMajorIterator lmbegin(){
					Indexer<Dim, Dims...> i;
					return LastDimensionMajorIterator(i, this);
				};

				LastDimensionMajorIterator lmend(){
					Indexer<Dim, Dims...> i;
					i.setValue();
					i.ldm_inc();
					return LastDimensionMajorIterator(i, this);
				};
		};

}
#endif
