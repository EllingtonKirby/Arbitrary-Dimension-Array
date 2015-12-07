#ifndef XXX_ARRAY_XXX
#define XXX_ARRAY_XXX
#include <type_traits>
#include <stddef.h>

namespace cs540{

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
		class Array{
			public:
				T container[Dim];
				
				Array();

				Array(const Array& A) : container(A.container)[];

				template<typename U>
				Array(const Array<U, Dim> &A){
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
					return container[index];
				};
 
		};

	template<typename T, size_t Dim, size_t... Dims>
		class Array{
			public:
				Array<T, Dims...> container[Dim];
			
				Array();

				Array(const Array& A) : container(A.container) {};

				template<typename U>
				Array(const Array<U, Dim, Dims...> &A){
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
				Array& operator=(const Array<U, Dim, Dims> &A){
					for(int i = 0; i < Dim; i++){
						container[i] = A.container[i];
					}
					
					return *this;
				}

				Array<T, Dims...>& operator[](int index){
					return container[index];
				};
		};

}
#endif
