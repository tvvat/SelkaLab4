#pragma once

using namespace std;
namespace Prog4 {

	template<typename T>
	class Vector {
	private:
		T* V1;
		static const int QUOTA = 10;
		int MS;
		int sze;
	public:

		int GetMaxsize() const noexcept { return MS; };
		T* GetV1() const noexcept { return V1; };
		int size() const noexcept { return sze; };
		Vector() {
			MS = QUOTA;
			sze = 0;
			V1 = new T[QUOTA + 1];
		}
		Vector(const Vector& Klass1) {
			sze = Klass1.size();
			MS = Klass1.GetMaxsize();
			V1 = new T[Klass1.size() + 1];
			memcpy(V1, Klass1.GetV1(), sizeof(T) * Klass1.size() + 1);
			//std::cout << " ------------------------------" << std::endl;

		}
		Vector(Vector&& Klass2) {
			sze = Klass2.size();
			MS = Klass2.GetMaxsize();
			V1 = Klass2.V1;
			Klass2.V1 = nullptr;
			/*char* ptr = Klass2.GetV1();
			V1 = ptr;*/
			//V1 = Klass2.GetV1();
			//std::cout << " This is MOVE CNST" << std::endl;

		}



		bool isEmpty() const {
			if (sze == 0)
				return 1;
			return 0;
		}
		void addMemory() {
			MS*= 2;
			T* tmp = V1;
			delete[] V1;
			V1 = new T[MS];
			for (int i = 0; i < sze; ++i) V1[i] = tmp[i];
			delete[] tmp;
		}

		void push_back(const T& value) {
			if (sze >= MS) addMemory();
			V1[sze++] = value;
		}



		void resize(size_t N) {
			QUOTA = N;
			MS = N;
			T* tmp = V1;
			V1 = new T[N];
			for (size_t i = 0; i < sze; ++i) V1[i] = tmp[i];
			delete[] tmp;

		}
		Vector &operator =(const Vector& Klass) {
			if (this != &Klass) {
				sze = Klass.size();
				MS = Klass.GetMaxsize();
				delete[] V1;
				V1 = new T[Klass.size()];
				memcpy(V1, Klass.GetV1(), sizeof(T) * Klass.size());
			}
			return *this;
		}

		Vector &operator =(Vector&& Klass) {
			int tmpsize = sze;
			sze = Klass.size;
			Klass.sze = tmpsize;
			tmpsize = MS;
			MS = Klass.MS;
			Klass.MS = tmpsize;
			T* tmp = V1;
			V1 = Klass.V1;
			Klass.V1 = tmp;
			return *this;
		}

		void SetSize(int SIZE) {
			if (SIZE < 1) {
				throw std::exception("Bad Size");
			}
			else {
				if (SIZE > sze) {
					T* tmp = new T[this->GetSize()];
					memcpy(tmp, V1, sizeof(T) * this->size());
					delete[] V1;
					V1 = new T[SIZE];
					memcpy(V1,tmp, sizeof(T) * this->size());
					delete[] tmp;
				}
				if (sze == SIZE)
					return;
				else {

				}

				sze = SIZE;
				//MS = (SIZE / 10 + 1) * QUOTA;
			}
		}


		std::istream& InputV(std::istream& is) {
			T* tmp = new T[MS + 1];
			is >> tmp;
			
			V1 = tmp;

			delete[] tmp;
			return is;
		}
		std::ostream& OutputV(std::ostream& os) const noexcept {
			T* tmp = GetV1();
			for (int i = 0; i < sze; i++) {
				os << tmp[i] << " ";
			}
			return os;
		}


		friend std::ostream& operator <<(std::ostream& out, const Vector& Tvector)
		{
			Tvector.OutputV(out);
			return out;
		}

		friend std::istream& operator >>(std::istream& is,   Vector& Tvector)
		{
			Tvector.InputV(is);
			return is;
		}

	
		T& operator[](size_t index) {/*
			sze++;*/
			return V1[index];
		}

		const T& operator[](size_t index) const {
			return V1[index];
		}


		T* begin() {
			return &V1[0];
		}

		const T* begin() const {
			return &V1[0];
		}

		T* end() {
			return &V1[sze];
		}

		const T* end() const {
			return &V1[sze];
		}



		~Vector() {
			delete[] V1;
		};


	};




}

