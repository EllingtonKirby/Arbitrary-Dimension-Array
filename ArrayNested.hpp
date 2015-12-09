#ifndef XXX_ARRAY_XXX
#define XXX_ARRAY_XXX
#include <type_traits>
#include <stddef.h>

namespace cs540{

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
	
	template<typename T, 0>
		class Array{
			public:
				Array() {
					#error "Container cannot have dimensions with size 0"
				};
		};

	template<typename T, 0, size_t... Dims>
		class Array{
			public:
				Array() {
					#error "Container cannot have dimensions with size 0"
				};
		};

	template<typename T, size_t Dim>
		class Array<T, Dim>{
			public:
				T container[Dim];
				
				//Array();

				//Array(const Array& A) : container(A.container)[];

				template<typename U>
				Array(const Array<U, Dim> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				//Array& operator=(const Array &A){
				//	if(this == &A){
				//		return *this;
				//	}
				//	for(int i = 0; i < Dim; i++){
				//		container[i] = A.container[i];
				//	}
				//	
				//	return *this;
				//};

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
				};

				class Indexer{
					public:
						Indexer() : m_index(0){};
						bool fdm_inc() {
							if(++m_index == Dim){
								return true;
							}
							return false;
						};

						void ldm_inc(){
							m_index++;
						};

						size_t m_index;
				};
 
		};

	template<typename T, size_t Dim, size_t... Dims>
		class Array<T, Dim, Dims...>{
			public:

				Array<T, Dims...> container[Dim];
			
				//Array();

				//Array(const Array& A) : container(A.container) {};

				template<typename U>
				Array(const Array<U, Dim, Dims...> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
				};

				//Array& operator=(const Array &A){
				//	if(this == &A){
				//		return *this;
				//	}
				//	for(int i = 0; i < Dim; i++){
				//		container[i] = A.container[i];
				//	}
				//	
				//	return *this;
				//};

				template<typename U>
				Array& operator=(const Array<U, Dim, Dims> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				}

				Array<T, Dims...>& operator[](int index){
					if(index < Dim && index >= 0){
						return container[index];
					}
				};

				class Indexer{
					template <typename U, size_t... Es>
					friend class typename Array<U, Es...>::Indexer;

					public:
						Indexer() : m_index(0){};
						bool fdm_inc(){
							if(m_nested.fdm_inc()){
								m_nested.m_index = 0;
								if(++m_index == Dim){
									return true;
								}	
							}	
							return false
						};

						void ldm_inc(){
							if(++m_index == Dim){
								m_index = 0;
								m_nested.ldm_inc();
							}
						};

						size_t m_index;
						typename Array<T, Ds...>::Indexer m_nested;
				};
						
				class FirstDimensionMajorIterator{
					public:
						Indexer indexer;

						FirstDimensionMajorIterator();

						FirstDimensionMajorIterator& operator++(){
							indexer.fdm_inc();
							return *this;	
						};

						FirstDimensionMajorIterator& operator++(int){
							auto temp = *this;
							indexer.fdm_inc();
							return temp;	
						};

						T& operator*() const{
						
						};
				};

				class LastDimensionMajorIterator{
					public:
						Indexer indexer;

						LastDimensionMajorIterator();

						LastDimensionMajorIterator& operator++(){
							indexer.ldm_inc();
							return *this;
						};

						LastDimensionMajorIterator& operator++(int){
							auto temp = *this;
							indexer.ldm_inc();
							return temp;
						};

						T& operator*() const{

						};
				};
		};

}
#endif
