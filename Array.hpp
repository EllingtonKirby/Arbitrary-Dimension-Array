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

	template<typename T, size_t... Dims> 
	class Array{
		private:
			int size;
			template <int N> struct Helper;
			
			template <int N>
			struct Helper {
				Helper(size_t i) : n(i) { }
				Helper<N - 1> operator[](size_t i) {
					return Helper<N - 1>(i*n);
				};
				const size_t n;
			};

		public:
			T container[calcProduct(Dims...)];
			
			Array() : size(calcProduct(Dims...)){	
				static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");
			};			

			Array(const Array& A) : size(A.size), container(A.container){
				static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");
			};

			template<typename U>
			Array(const Array<U, Dims...> &A) : size(A.size){
				static_assert(calcProduct(Dims...), "Container cannot have dimension with size 0");
				for(int i = 0; i < size; i++){
					container[i] = A.container[i];
				}
			};
			
			Array& operator=(const Array &A){
				if(this == &A){
					return *this;
				}

				size = A.size;
				for(int i = 0; i < size; i++){
					container[i] = A.container[i];
				}		
				return *this;
			};
			
			template<typename U>
			Array& operator=(const Array<U, Dims...> &A){	
				size = A.size;
				for(int i = 0; i < size; i++){
					container[i] = A.container[i];
				}	
				return *this;	
			};
			
			inline Helper<2> operator[](size_t i){
				return Helper<2>(i);
			};
		
			class FirstDimensionMajorIterator{
				private:
					int index;
				public:
					FirstDimensionMajorIterator();

					FirstDimensionMajorIterator& operator++();

					FirstDimensionMajorIterator& operator++(int);

					T& operator*() const{
						return container[index];
					};
			};

			class LastDimensionMajorIterator{
				private: 
					int index;
				public:
					LastDimensionMajorIterator();

					LastDimensionMajorIterator& operator++();

					LastDimensionMajorIterator& operator++(int);

					T& operator*() const{
						return container[index];
					};
			};
	};

	template <typename T, size_t... Dims>
	template<>
	struct typename Array<T, Dims...>::Helper<0> {
		Helper(size_t i) : n(i) {}
		T& operator[](size_t i) {
			return container[n*i];
		}
		const size_t n;
	};		


}

#endif
