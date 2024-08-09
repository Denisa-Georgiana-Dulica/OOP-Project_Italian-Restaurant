#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
//clasa 1 //PREPARATE - PREPARAT
class Preparate
{
	const int id_preparat;
	char* denumire_preparat = nullptr;
	float pret = 0;
	static int nr_preparate;

public:
	Preparate() :id_preparat(id_preparat)
	{

	}

	//constructor cu parametrii 1
	Preparate(int id_preparat) :id_preparat(id_preparat)
	{

	}

	//constructor cu parametrii 2
	Preparate(int id_preparat, const char* denumire_preparat, float pret) :id_preparat(id_preparat)
	{
		if (denumire_preparat != nullptr && strlen(denumire_preparat) >= 3)
		{
			this->denumire_preparat = new char[strlen(denumire_preparat) + 1];
			strcpy(this->denumire_preparat, denumire_preparat);
		}
		else
		{
			this->denumire_preparat = new char[strlen("N/A") + 1];
			strcpy(this->denumire_preparat, "N/A");
		}
		if (pret > 0)
		{
			this->pret = pret;
		}
		nr_preparate++;
	}

	//constructor de copiere
	Preparate(const Preparate& m):id_preparat(m.id_preparat)
	{
		
		if (m.denumire_preparat != nullptr && strlen(m.denumire_preparat) >= 3)
		{
			this->denumire_preparat = new char[strlen(m.denumire_preparat) + 1];
			strcpy(this->denumire_preparat, m.denumire_preparat);
		}
		else
		{
			this->denumire_preparat = new char[strlen("N/A") + 1];
			strcpy(this->denumire_preparat, "N / A");
		}
		if (m.pret > 0)
		{
			this->pret = m.pret;
		}
		nr_preparate++;
	}

	//operator =
	Preparate& operator=(const Preparate& m)
	{
		
		if (this != &m)
		{
			delete[] this->denumire_preparat;
			this->denumire_preparat = nullptr;
			if (m.denumire_preparat != nullptr && strlen(m.denumire_preparat) >= 4)
			{
				this->denumire_preparat = new char[strlen(m.denumire_preparat) + 1];
				strcpy(this->denumire_preparat, m.denumire_preparat);
			}
			else
			{
				this->denumire_preparat = new char[strlen("N/A") + 1];
				strcpy(this->denumire_preparat, "N/A");
			}
			if (m.pret > 0)
			{
				this->pret = m.pret;
			}
			nr_preparate++;
		}
		return *this;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Preparate& m)
	{
		out << "\n----------------------------------";
		if (m.denumire_preparat != nullptr && strlen(m.denumire_preparat) >= 3)
		{
			out << "\nDenumire preparat: " << m.denumire_preparat;
		}
		else
			out << "\nDenumire preparat: -";
		out << "\nPretul preparatului: " << m.pret<<" lei ";
		out << "\n----------------------------------";
		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Preparate& m)
	{
		delete[] m.denumire_preparat;
		m.denumire_preparat = nullptr;
		cout << "\nIntroduceti felul de Pizza sau Paste: ";
		in >> ws;
		string buffer;
		getline(in, buffer);
		m.denumire_preparat = new char[buffer.size() + 1];
		strcpy(m.denumire_preparat, buffer.data());
		cout << "\nIntroduceti pretul pentru acest preparat: ";
		in >> m.pret;
		if (m.pret < 0)
			m.pret = 0;
		return in;
	}
	//get si set
	int getId() const
	{
		return this->id_preparat;
	}
	const char* getDenumirePreparat()
	{
		
			return this->denumire_preparat;
		
	}
	void setDenumirePreparat(const char* denumire_preparat)
	{
		if (denumire_preparat != nullptr && strlen(denumire_preparat) >= 3)
		{
			delete[] this->denumire_preparat;
			this->denumire_preparat = new char[strlen(denumire_preparat) + 1];
			strcpy(this->denumire_preparat, denumire_preparat);
		}
		else
		{
			this->denumire_preparat = new char[strlen("N/A") + 1];
			strcpy(this->denumire_preparat, "N/A");
		}
		
	}
	float getPret()
	{
		return this->pret;
	}
	void setPret(float pret)
	{
		if (pret > 0)
		{
			this->pret = pret;
		}
	}
	
	static int getNrPreparate()
	{
		return Preparate::nr_preparate;
	}
	static void setNrPreparate(int nrPreparate)
	{
		if (nrPreparate > 0)
		{
			Preparate::nr_preparate = nrPreparate;
		}
	}
	//operator cast (IN METODA DE AFISARE 1)
	explicit operator float()
	{
		return this->pret;
	}
	//operator +
	Preparate operator+(const char* extra_produs)
	{
		if (strlen(extra_produs) >= 5 && extra_produs != nullptr)
		{
			Preparate p = *this;
			if (p.denumire_preparat != nullptr && p.pret > 0)
			{
				char* extra = new char[strlen(extra_produs) + strlen(p.denumire_preparat) + 2];
				strcpy(extra, p.denumire_preparat);
				strcat(extra, " + ");
				strcat(extra, extra_produs);
				delete[] p.denumire_preparat;
				p.denumire_preparat = new char[strlen(extra) + 1];
				strcpy(p.denumire_preparat, extra);
				p.pret += 10;
			}
			return p;
		}
	}

	//operator>
	bool operator>(int reducere)
	{
		if (reducere > 0 && this->pret > 0)
		{
			if (this->pret > reducere)
			{
				return true;
			}
			return false;
		}
	}
	//operator ==
	bool operator==(const Preparate& p)
	{
		if (this->pret > 0 && p.pret > 0)
		{
			if (this->pret == p.pret)
			{
				return true;
			}
			return false;
		}
	}
	//metoda de afisare 1
	static void pretMax(Preparate* preparate, int nr_preparate)
	{
		if (nr_preparate > 0 && preparate != nullptr)
		{
			float max = preparate[0].getPret();
			string denumire = preparate[0].getDenumirePreparat();
			for (int i = 0; i < nr_preparate; i++)
			{
				//operator cast
				float pret = (float)preparate[i];
				if (max < pret)
				{
					max = pret;
					denumire = preparate[i].getDenumirePreparat();
				}
			}
			cout << "\nPreparatul cu pretul maxim de " << max << " lei este " << denumire;
		}
	}
	//metoda de afisare 2
	static void pretMin(Preparate* preparate, int nr_preparate)
	{
		if (nr_preparate > 0 && preparate != nullptr)
		{
			float min = preparate[0].getPret();
			string denumire = preparate[0].getDenumirePreparat();
			for (int i = 0; i < nr_preparate; i++)
			{
				float pret = (float)preparate[i];
				if (min> pret)
				{
					min = pret;
					denumire = preparate[i].getDenumirePreparat();
				}
			}
			cout << "\nPreparatul cu pretul minim de " << min << " lei este " << denumire;
		}
	}
	
	//destructor
	~Preparate()
	{
		delete[] this->denumire_preparat;
		this->denumire_preparat = nullptr;
	}
};
int Preparate::nr_preparate = 0;

//clasa 2
class Meniu
{
	Preparate* preparate=nullptr;
	int nrProduseMeniu = 0;
	
public:
	Meniu()
	{

	}

	//constructor cu parametrii 
	Meniu(Preparate* preparate, int nrProduseMeniu)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] =preparate[i];
			}
		}
	}

	//constructor de copiere
	Meniu(const Meniu& m)
	{
		if (m.nrProduseMeniu > 0 && m.preparate != nullptr)
		{
			this->nrProduseMeniu = m.nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = m.preparate[i];
			}
		}
	}

	//operator =
	Meniu& operator=(const Meniu& m)
	{
		if (this != &m)
		{
			delete[] this->preparate;
			this->preparate = nullptr;
			if (m.nrProduseMeniu > 0 && m.preparate != nullptr)
			{
				this->nrProduseMeniu = m.nrProduseMeniu;
				this->preparate = new Preparate[this->nrProduseMeniu];
				for (int i = 0; i < this->nrProduseMeniu; i++)
				{
					this->preparate[i] = m.preparate[i];
				}
			}
		}
		return *this;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Meniu& m)
	{
		out << "\n--------------------------";
		out << "\nNumar preparate: " << m.nrProduseMeniu;
		out << endl;
		out << "\nMeniu: \n";
		for (int i = 0; i < m.nrProduseMeniu; i++)
		{
			out <<"\nDenumire preparat: " << m.preparate[i].getDenumirePreparat()<< "\nPretul preparatului: " << m.preparate[i].getPret() << " lei "<<endl;
		}
		out << "\n--------------------------";
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Meniu& m)
	{
		
		delete[] m.preparate;
		m.preparate = nullptr;
		cout << "\nIntroduceti numarul de produse din meniu: ";
		in >> m.nrProduseMeniu;
		m.preparate = new Preparate[m.nrProduseMeniu];
		for (int i = 0; i < m.nrProduseMeniu; i++)
		{
			cout << "\nIntroduceti informatiile pentru preparatul " << i + 1 << " : ";
			in >> m.preparate[i];
		}
		return in;
	}
	//get si set
	int getNrProduseMeniu()
	{
		return this->nrProduseMeniu;
	}
	int getPreparateVegane()
	{
		if (this->preparate != nullptr && this->nrProduseMeniu > 0)
		{
			int nr = 0;
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				if (strstr(preparate[i].getDenumirePreparat(), "vegana"))
				{
					nr++;
				}
			}
			return nr;
		}
	}

	//destructor
	~Meniu()
	{
		delete[] this->preparate;
		this->preparate = nullptr;
	}

	//metoda de afisare 1
	void afisareMeniu()
	{
		if (preparate != nullptr && nrProduseMeniu > 0)
		{
			for (int i = 0; i < nrProduseMeniu; i++)
			{
				cout << "\nPreparat " << i + 1 << " : " << preparate[i].getDenumirePreparat();
				cout << " - Pretul preparatului " << i + 1 << " : " << preparate[i].getPret();
			}
		}
	}

	//metoda afisare 2 (PRODUSE VEGANE)
	string* operator[](const char* vegana)
	{
		if (this->preparate != nullptr && this->nrProduseMeniu > 0)
		{
			int nr = 0;
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				if (strstr(preparate[i].getDenumirePreparat(),vegana))
				{
					nr++; 
				}
			}
			string* vegane = new string[nr + 1];
			int pozitie = 0;
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				if (strstr(preparate[i].getDenumirePreparat(), vegana))
				{
					vegane[pozitie] = preparate[i].getDenumirePreparat();
					pozitie++;
				}
			}
			return vegane;
		}
	}
	
	
};

//clasa 3
class MateriePrima
{
	char* denumireMateriePrima = nullptr;
	float cantitateMaxima = 0;
	static int nrMateriiPrime;
public:
	MateriePrima()
	{
	}

	//constructor cu parametrii 1
	MateriePrima(const char* denumireMateriePrima, float cantitateMaxima)
	{
		
		if (denumireMateriePrima != nullptr && strlen(denumireMateriePrima) >= 3)
		{
			this->denumireMateriePrima = new char[strlen(denumireMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, denumireMateriePrima);
		}
		else
		{
			this->denumireMateriePrima = new char[strlen("N/A") + 1];
			strcpy(this->denumireMateriePrima, "N/A");
		}
		if (cantitateMaxima > 0)
			this->cantitateMaxima = cantitateMaxima;
		nrMateriiPrime++;
	}

	//constructor copiere
	MateriePrima(const MateriePrima& mp)
	{
		if (mp.denumireMateriePrima != nullptr && strlen(mp.denumireMateriePrima) >= 3)
		{
			this->denumireMateriePrima = new char[strlen(mp.denumireMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, mp.denumireMateriePrima);
		}
		else
		{
			this->denumireMateriePrima = new char[strlen("N/A") + 1];
			strcpy(this->denumireMateriePrima, "N/A");
		}
		if (mp.cantitateMaxima > 0)
			this->cantitateMaxima = mp.cantitateMaxima;
		
	}

	//operator =
	MateriePrima& operator=(const MateriePrima& mp)
	{
		if (this != &mp)
		{
			delete[] this->denumireMateriePrima;
			this->denumireMateriePrima = nullptr;
			if (mp.denumireMateriePrima != nullptr && strlen(mp.denumireMateriePrima) >= 3)
			{
				this->denumireMateriePrima = new char[strlen(mp.denumireMateriePrima) + 1];
				strcpy(this->denumireMateriePrima, mp.denumireMateriePrima);
			}
			else
			{
				this->denumireMateriePrima = new char[strlen("N/A") + 1];
				strcpy(this->denumireMateriePrima, "N/A");
			}
			if (mp.cantitateMaxima > 0)
				this->cantitateMaxima = mp.cantitateMaxima;
		
		}
		return *this;
	}

	//operator<<
	friend ostream& operator<<(ostream& out, const MateriePrima& mp)
	{
		out << "\n---------------------------------------";
		out << "\nDenumire materie prima: " << mp.denumireMateriePrima;
		out << "\nCantitate disponibila: " << mp.cantitateMaxima;
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, MateriePrima& mp)
	{
		delete[] mp.denumireMateriePrima;
		mp.denumireMateriePrima = nullptr;
		cout << "\nIntroduceti materia prima: ";
		in >> ws;
		string buffer;
		getline(in, buffer);
		mp.denumireMateriePrima = new char[buffer.size() + 1];
		strcpy(mp.denumireMateriePrima, buffer.data());
		cout << "\nIntroduceti cantitatea maxima pentru aceasta: ";
		in >> mp.cantitateMaxima;
		if (mp.cantitateMaxima < 0)
			mp.cantitateMaxima = 0;
		return in;
	}
	//destructor
	~MateriePrima()
	{
		delete[] this->denumireMateriePrima;
		this->denumireMateriePrima = nullptr;
	}
	//get si set
	const char* getDenumireMateriePrima()
	{
		return this->denumireMateriePrima;
	}
	void setDenumireMateriePrima(const char* denumire)
	{
		if (denumire != nullptr && strlen(denumire) >= 3)
		{
			this->denumireMateriePrima = new char[strlen(denumire) + 1];
			strcpy(this->denumireMateriePrima,denumire);
		}
		else
		{
			this->denumireMateriePrima = new char[strlen("N/A") + 1];
			strcpy(this->denumireMateriePrima, "N/A");
		}
	}
	float getCantitateMaxima()
	{
		return this->cantitateMaxima;
	}
	void setCantitateMax(float cantitateConsumata)
	{
		if (cantitateConsumata > 0 && this->cantitateMaxima >= cantitateConsumata)
		{
			this->cantitateMaxima -= cantitateConsumata;
			//cout << this->cantitateMaxima << " ";
		}
		else
			cout << "\n Nu se poate face comanda, nu sunt destule materii prime";
	}
	
	static int getNrMateriiPrime()
	{
		return MateriePrima::nrMateriiPrime;
	}
	static void setNrMateriiPrime(int nrMateriiPrime)
	{
		if (nrMateriiPrime > 0)
		{
			MateriePrima::nrMateriiPrime = nrMateriiPrime;
		}
	}
	//metoda afisare 1
	static float afisareStocCelMaiMic(MateriePrima* materiePrima)
	{
		if (materiePrima != nullptr && nrMateriiPrime > 0)
		{
			float min = materiePrima[0].getCantitateMaxima();
			for (int i = 0; i < nrMateriiPrime; i++)
			{
				if (min > materiePrima[i].getCantitateMaxima())
				{
					min = materiePrima[i].getCantitateMaxima();
				}
			}
			return min;
		}
	}
	//metoda afisare 2
	static float afisareStocCelMaiMare(MateriePrima* materiePrima)
	{
		if (materiePrima != nullptr && nrMateriiPrime > 0)
		{
			float max = materiePrima[0].getCantitateMaxima();
			for (int i = 0; i < nrMateriiPrime; i++)
			{
				if (max < materiePrima[i].getCantitateMaxima())
				{
					max = materiePrima[i].getCantitateMaxima();
				}
			}
			return max;
		}
	}
	//operator !
	bool operator!()
	{
		if (this->cantitateMaxima > 0)
			return true;
		return false;
	}
	//operator ++ postincrementare
	MateriePrima operator++(int)
	{
		MateriePrima mp = *this;
		this->cantitateMaxima++;
		return mp;
	}
	//operator ++ preincremenatre
	MateriePrima& operator++()
	{
		MateriePrima mp = *this;
		this->cantitateMaxima++;
		return *this;
	}
};
int MateriePrima::nrMateriiPrime = 0;

//clasa 4
class Retetar
{
	MateriePrima* materiePrima=nullptr;
	Preparate* preparate=nullptr;
	string* Ingrediente = nullptr;
	int nrIngrediente = 0;
	float* cantitate = nullptr;
	int nrProduseMeniu = 0;
	float* nrCalorii = nullptr;
public:
	Retetar()
	{

	}
	//constructor cu parametrii 1 
	Retetar(Preparate* preparate, string* Ingrediente, float* cantitate,int nrProduseMeniu, int nrIngrediente)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = preparate[i];
			}
		}
		if (nrIngrediente > 0 && Ingrediente != nullptr && cantitate!=nullptr)
		{
			this->nrIngrediente = nrIngrediente;
			this->Ingrediente = new string[this->nrIngrediente];
			this->cantitate = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->Ingrediente[i] = Ingrediente[i];
				this->cantitate[i] = cantitate[i];
			}
		}
		
	}
	//constructor cu parametrii 2
	Retetar(MateriePrima* materiePrima, float* nrCalorii)
	{
		if (materiePrima != nullptr && nrCalorii != nullptr && MateriePrima::getNrMateriiPrime() > 0)
		{
			this->materiePrima = new MateriePrima[MateriePrima::getNrMateriiPrime()];
			this->nrCalorii = new float[MateriePrima::getNrMateriiPrime()];
			for (int i = 0; i < MateriePrima::getNrMateriiPrime(); i++)
			{
				this->materiePrima[i] = materiePrima[i];
				this->nrCalorii[i] = nrCalorii[i];
			}
		}
	}
	
	//constructor de copiere
	Retetar(const Retetar& r)
	{
		if (r.nrProduseMeniu > 0 && r.preparate != nullptr)
		{
			this->nrProduseMeniu = r.nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = r.preparate[i];
			}
		}
		if (r.nrIngrediente > 0 && r.Ingrediente != nullptr && r.cantitate != nullptr)
		{
			this->nrIngrediente = r.nrIngrediente;
			this->Ingrediente = new string[this->nrIngrediente];
			this->cantitate = new float[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->Ingrediente[i] = r.Ingrediente[i];
				this->cantitate[i] = r.cantitate[i];
			}
		}
		

	}

	//operator =
	Retetar& operator=(const Retetar& r)
	{
		if (this != &r)
		{
			delete[] this->preparate;
			this->preparate = nullptr;
			delete[] this->Ingrediente;
			this->Ingrediente = nullptr;
			delete[] this->cantitate;
			this->cantitate = nullptr;
			
			if (r.nrProduseMeniu > 0 && r.preparate != nullptr)
			{
				this->nrProduseMeniu = r.nrProduseMeniu;
				this->preparate = new Preparate[this->nrProduseMeniu];
				for (int i = 0; i < this->nrProduseMeniu; i++)
				{
					this->preparate[i] = r.preparate[i];
				}
			}
			if (r.nrIngrediente > 0 && r.Ingrediente != nullptr && r.cantitate != nullptr)
			{
				this->nrIngrediente = r.nrIngrediente;
				this->Ingrediente = new string[this->nrIngrediente];
				this->cantitate = new float[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++)
				{
					this->Ingrediente[i] = r.Ingrediente[i];
					this->cantitate[i] = r.cantitate[i];
				}
			}
			
		}
		return *this;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Retetar& r)
	{
		out << "\n-----------------------------------";
		for (int i = 0; i < r.nrProduseMeniu; i++)
		{
			out << "\nDenumire preparat: " << r.preparate[i].getDenumirePreparat();
			out << endl;
			out << "\nNumar ingrediente: " << r.nrIngrediente;
			if (r.nrIngrediente > 0 && r.Ingrediente != nullptr && r.cantitate != nullptr)
			{
				out << "\nIngrediente: \n";
				for (int i = 0; i < r.nrIngrediente; i++)
				{
					out << r.Ingrediente[i] << " - " << r.cantitate[i] <<" grame "<< endl;
				}
			}
			else
			{
				out << "\nIngrediente: - ";
			}
		}
		out << "\n-----------------------------------";
		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Retetar& r)
	{
		delete[] r.preparate;
		r.preparate = nullptr;
		delete[] r.Ingrediente;
		r.Ingrediente = nullptr;
		delete[] r.cantitate;
		r.cantitate = nullptr;
		r.nrProduseMeniu = 1;
		r.preparate = new Preparate[r.nrProduseMeniu];
		for (int i = 0; i < r.nrProduseMeniu; i++)
		{
			in >> r.preparate[i];
		}
		cout << "\nIntroduceti numarul de ingrediente: ";
		in >> r.nrIngrediente;
		r.Ingrediente = new string[r.nrIngrediente];
		r.cantitate = new float[r.nrIngrediente];
		for (int i = 0; i < r.nrIngrediente; i++)
		{
			cout << "\nIntroduceti denumirea ingredientului "<<i+1<<" : ";
			in >> r.Ingrediente[i];
			cout << "\nIntroduceti cantitatea necesara " << i + 1 << " : ";
			in >> r.cantitate[i];
		}
		return in;
	}
	//metoda de afisare 1
	float afisareCalorii(string preparat,float* nrCalorii,MateriePrima* materiePrima)
	{
		if (materiePrima != nullptr && nrCalorii != nullptr && MateriePrima::getNrMateriiPrime() > 0)
		{

			float sumaCalorii = 0;
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				for (int j = 0; j < MateriePrima::getNrMateriiPrime(); j++)
				{
					if (this->Ingrediente[i] == materiePrima[j].getDenumireMateriePrima())
					{
						sumaCalorii += (this->cantitate[i] / 100) * nrCalorii[j];
					}
				}
			}
			return sumaCalorii;
		}
		
	}
	//metoda de prelucrare 2
	bool CalculeazaCantitate(string preparat, int cantitateDorita, MateriePrima* materiePrima)
	{
		bool preparatGasit = false;
		int ok = 1;
		if (preparat.size() >= 3 && cantitateDorita > 0)
		{
			if (this->preparate != nullptr && this->nrProduseMeniu > 0)
			{
				for (int i = 0; i < this->nrProduseMeniu; i++)
				{
					if (preparate[i].getDenumirePreparat() == preparat)
					{
						preparatGasit = true;
						float* cantitate_necesara = new float[this->nrIngrediente];
						for (int k = 0; k < this->nrIngrediente; k++)
						{
							cantitate_necesara[k] = this->cantitate[k] * cantitateDorita;
						}
						for (int k = 0; k < this->nrIngrediente; k++)
						{
							for (int j = 0; j < MateriePrima::getNrMateriiPrime(); j++)
							{
								if (this->Ingrediente[k] == materiePrima[j].getDenumireMateriePrima())
								{
									if (cantitate_necesara[k] > materiePrima[j].getCantitateMaxima())
									{
										ok = 0;
										break;
									}
									
								}
							
							}
						}
						
						if (ok == 1)
						{
							
							for (int k = 0; k < this->nrIngrediente; k++)
							{
								for (int j = 0; j < MateriePrima::getNrMateriiPrime(); j++)
								{
									if (this->Ingrediente[k] == materiePrima[j].getDenumireMateriePrima())
									{
										materiePrima[j].setCantitateMax(cantitate_necesara[k]);
									}
								}
							}
							
						}

					}
					
				}
			}
		}
		if (ok == 1 && preparatGasit==true)
		{

			cout << "\nComanda este gata in "<<11*cantitateDorita<<" minute !";
			return true;
			
		}
		else
		{
			cout << "\nNu se poate face aceasta comanda (insuficiente materii prime) !";
			return false;
		}
	}
	
	int getNrIngrediente()
	{
		return this->nrIngrediente;
	}
	void setIngrediente(int nrIngrediente,string* Ingrediente,float* cantitate)
	{
		if (nrIngrediente > 0 && Ingrediente!=nullptr && cantitate!=nullptr)
		{
			this->nrIngrediente = nrIngrediente;
			delete[] this->Ingrediente;
			delete[] this->cantitate;
			for (int i = 0; i < this->nrIngrediente; i++)
			{
				this->Ingrediente[i] = Ingrediente[i];
				this->cantitate[i] = cantitate[i];
			}
		}
	}
	float* getCantitate()
	{
		return cantitate;
	}
	string* getIngrediente()
	{
		return Ingrediente;
	}
	int getNrProduseMeniu()
	{
		return this->nrProduseMeniu;
	}
	void setNrProduseMeniu(int nrProduseMediu)
	{
		if (nrProduseMeniu > 0)
		{
			this->nrProduseMeniu = nrProduseMeniu;
		}
	}
	
	//destructor
	~Retetar()
	{
		delete[] this->preparate;
		this->preparate = nullptr;
		delete[] this->Ingrediente;
		this->Ingrediente = nullptr;
		delete[] this->cantitate;
		this->cantitate = nullptr;
		delete[] this->materiePrima;
		this->materiePrima = nullptr;
		delete[] this->nrCalorii;
		this->nrCalorii = nullptr;
	}

};

//clasa 5
class Restaurant_Italian
{
	Preparate* preparate = nullptr;
	int nrProduseMeniu = 0;
	Retetar* retete = nullptr; //RESTAURANTUL CARE MAI MULTE RETETARE ? NU, CONCEPT GRESIT
public:
	Restaurant_Italian()
	{

	}

	//constructor cu parametrii 1
	Restaurant_Italian(Preparate* preparate, Retetar* retete,int nrProduseMeniu)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			this->retete = new Retetar[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = preparate[i];
				this->retete[i] = retete[i];
			}
		}
		
	}
	//constructor de copiere
	Restaurant_Italian(const Restaurant_Italian& ri)
	{
		if (ri.nrProduseMeniu > 0 && ri.preparate != nullptr)
		{
			this->nrProduseMeniu = ri.nrProduseMeniu;
			this->preparate = new Preparate[this->nrProduseMeniu];
			this->retete = new Retetar[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = ri.preparate[i];
				this->retete[i] = ri.retete[i];
			}
		}
	}
	//operator <<
	friend ostream& operator<<(ostream& out, const Restaurant_Italian& ri)
	{
		out << "-------------------------";
		out << "\nNumar preparate: "<<ri.nrProduseMeniu;
		for (int i = 0; i < ri.nrProduseMeniu; i++)
		{
			out << ri.retete[i] << endl;
		}

		return out;
	}
	//operator >>
	friend istream& operator>>(istream& in, Restaurant_Italian& ri)
	{
		delete[] ri.retete;
		ri.retete = nullptr;
		cout << "\nIntroduceti numarul de produse din meniul restaurantului: ";
		in >> ri.nrProduseMeniu;
		ri.retete = new Retetar[ri.nrProduseMeniu];
		for (int i = 0; i < ri.nrProduseMeniu; i++)
		{
			cout << "\nIntroduceti informatiile legate de restaurant pentru produsul "<<i+1<<" : ";
			in >> ri.retete[i];
		}
		return in;

	}
	//operator =
	Restaurant_Italian& operator=(const Restaurant_Italian& ri)
	{
		if (this != &ri)
		{
			delete[] this->preparate;
			this->preparate = nullptr;
			delete[] this->retete;
			this->retete = nullptr;
			if (ri.nrProduseMeniu > 0 && ri.preparate != nullptr)
			{
				this->nrProduseMeniu = ri.nrProduseMeniu;
				this->preparate = new Preparate[this->nrProduseMeniu];
				this->retete = new Retetar[this->nrProduseMeniu];
				for (int i = 0; i < this->nrProduseMeniu; i++)
				{
					this->preparate[i] = ri.preparate[i];
					this->retete[i] = ri.retete[i];
				}
			}
		}
		return *this;
	}

	//metoda de afisare 1
	void afiseazaRetete(string preparat)
	{
		if (this->retete != nullptr && this->preparate!=nullptr && this->nrProduseMeniu > 0)
		{
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				if (preparat == preparate[i].getDenumirePreparat())
				{
					cout << retete[i];
				}
			}
		}
	}
	//metoda de prelucrare 2
	float Reducere(int reducere,string preparat,float cantitate)
	{
		if (preparate != nullptr && nrProduseMeniu > 0)
		{
			float suma = 0;
			for (int i = 0; i < nrProduseMeniu; i++)
			{
				if (preparat == preparate[i].getDenumirePreparat())
				{
					bool aplicare = preparate[i].operator>(reducere);
					if (aplicare == false)
					{
						suma = preparate[i].getPret() * cantitate;
						cout << "\nPret total: " << suma << " lei ";
						return suma;
					}
					if (aplicare == true)
					{
						float pret_nou = preparate[i].getPret() - preparate[i].getPret() * 0.1;
						preparate[i].setPret(pret_nou);
						cout << "\nPretul preparatului depaseste 40 de lei";
						cout << "\nPretul cu reducere aplicata pentru " << preparate[i].getDenumirePreparat() << " este " << preparate[i].getPret() * cantitate << " lei !";
						return preparate[i].getPret() * cantitate;
					}
				}
			}
		}
	}
	
	//destructor
	~Restaurant_Italian()
	{
		delete[] this->preparate;
		this->preparate = nullptr;
		delete[] this->retete;
		this->retete = nullptr;
	}
};

int main()
{
	//clasa 1
	Preparate p1(1, "Spaghetti Bolognese", 35);
	Preparate p2(2, "Penne Carbonara", 37);
	Preparate p3(3, "Linguine alle Vongole", 45);
	Preparate p4(4, "Fettuccine Alfredo", 39);
	Preparate p5(5, "Pasta vegana alla Norma", 40);
	Preparate p6(6, "Pizza Margherita", 30);
	Preparate p7(7, "Pizza Pepperoni", 33);
	Preparate p8(8, "Pizza Quattro Formaggi", 41);
	Preparate p9(9, "Pizza vegana", 42);
	Preparate p10(10, "Pizza Diavola", 34);
	int nr_total_preparate = Preparate::getNrPreparate();
	string meniu[] = { "Spaghetti Bolognese","Penne Carbonara",  "Linguine alle Vongole" ,"Fettuccine Alfredo","Pasta vegana alla Norma", "Pizza Margherita",  "Pizza Pepperoni" ,"Pizza Quattro Formaggi" ,"Pizza vegana" ,"Pizza Diavola" };
	

	//clasa 2
	Preparate lista_preparate[] = { p1,p2,p3,p4,p5,p6,p7,p8,p9,p10};
	Meniu m(lista_preparate, 10);

	//clasa 4
	Preparate lista1[] = { p1 };
	string ingrediente1[] = {"Paste", "Carne tocata","Ceapa","Usturoi","Rosii","Morcov" };
	float cantitate1[] = { 100,100, 50,10,100,50 };
	Retetar r1(lista1, ingrediente1, cantitate1,1,6);
	Preparate lista2[] = { p2 };
	string ingrediente2[] = {"Paste","Bacon","Oua","Parmezan","Usturoi"};
	float cantitate2[] = { 100, 50,100,50,5 };
	Retetar r2(lista2, ingrediente2, cantitate2, 1, 5);
	Preparate lista3[] = { p3 };
	string ingrediente3[] = { "Paste","Midii","Usturoi","Pere"};
	float cantitate3[] = { 100, 100,5,50 };
	Retetar r3(lista3, ingrediente3, cantitate3, 1, 4);
	Preparate lista4[] = { p4 };
	string ingrediente4[] = { "Paste","Unt","Smantana","Parmezan" };
	float cantitate4[] = { 100, 40,50,50 };
	Retetar r4(lista4, ingrediente4, cantitate4, 1, 4);
	Preparate lista5[] = { p5 };
	string ingrediente5[] = { "Paste","Vinete","Usturoi","Rosii","Busuioc" };
	float cantitate5[] = { 100, 50,5,150,3 };
	Retetar r5(lista5, ingrediente5, cantitate5, 1, 5);
	Preparate lista6[] = { p6 };
	string ingrediente6[] = { "Aluat pizza","Sos rosii","Mozzarella","Rosii","Busuioc" };
	float cantitate6[] = { 200, 100,125,50,3 };
	Retetar r6(lista6, ingrediente6, cantitate6, 1, 5);
	Preparate lista7[] = { p7 };
	string ingrediente7[] = { "Aluat pizza","Sos rosii","Mozzarella","Pepperoni","Oregano" };
	float cantitate7[] = { 200, 100,125,50,3 };
	Retetar r7(lista7, ingrediente7, cantitate7, 1, 5);
	Preparate lista8[] = { p8 };
	string ingrediente8[] = { "Aluat pizza","Sos bechamel","Mozzarella","Gorgonzola","Parmezan","Ricotta"};
	float cantitate8[] = { 200, 100,50,50,50,50 };
	Retetar r8(lista8, ingrediente8, cantitate8, 1, 6);
	Preparate lista9[] = { p9 };
	string ingrediente9[] = { "Aluat pizza","Sos rosii","Tofu","Ardei","Ciuperci","Oregano"};
	float cantitate9[] = { 200, 100,150,50,50,3 };
	Retetar r9(lista9, ingrediente9, cantitate9, 1, 6);
	Preparate lista10[] = { p10 };
	string ingrediente10[] = { "Aluat pizza","Sos rosii","Mozzarella","Salam picant","Ardei iute","Oregano" };
	float cantitate10[] = { 200, 100,125,50,10,3 };
	Retetar r10(lista10, ingrediente10, cantitate10, 1, 6);
	
	Retetar listaRetete[] = { r1,r2,r3,r4,r5,r6,r7,r8,r9,r10 };
	Preparate p11;
	Preparate paste[] = { p1,p2,p3,p4,p5 };
	Preparate pizza[] = { p6,p7,p8,p9,p10 };

	//clasa 3
	MateriePrima m1("Paste", 800); 
	MateriePrima m2("Carne tocata", 400);
	MateriePrima m3("Ceapa", 300);
	MateriePrima m4("Usturoi", 230);
	MateriePrima m5("Rosii", 650);
	MateriePrima m6("Morcov", 300);
	MateriePrima m7("Bacon", 300);
	MateriePrima m8("Oua", 400);
	MateriePrima m9("Parmezan", 500);
	MateriePrima m10("Midii", 300);
	MateriePrima m11("Pere", 100);
	MateriePrima m12("Unt", 200);
	MateriePrima m13("Smantana", 200);
	MateriePrima m14("Vinete", 200);
	MateriePrima m15("Busuioc", 200);
	MateriePrima m16("Aluat pizza", 5000);
	MateriePrima m17("Sos rosii", 1000);
	MateriePrima m18("Mozzarella", 2000);
	MateriePrima m19("Pepperoni", 500);
	MateriePrima m20("Oregano", 200);
	MateriePrima m21("Sos bechamel", 500);
	MateriePrima m22("Gorgonzola", 200);
	MateriePrima m23("Ricotta", 200);
	MateriePrima m24("Tofu", 600);
	MateriePrima m25("Ardei", 200);
	MateriePrima m26("Ciuperci", 200);
	MateriePrima m27("Salam picant", 200);
	MateriePrima m28("Ardei iute", 200);
	MateriePrima listaMateriiPrima[] = { m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15,m16,m17,m18,m19,m20,m21,m22,m23,m24,m25,m26,m27,m28 };
	int nrMateriiPrime = MateriePrima::getNrMateriiPrime();
	float nrCalorii[] = { 350,250,50,10,10,5,300,75,400,90,20,700,200,50,5,250,20,200,200,5,100,350,150,150,10,20,350,30 };
	
	//clasa 5
	Restaurant_Italian r(lista_preparate, listaRetete, 10);
	Retetar rc(listaMateriiPrima, nrCalorii);

	string optiune;
	string preparat;
	int cantitate;
	do
	{
		cout << endl;
		cout << "\nINTRODUCETI IN ACEST FORMAT !" << "\n";
		cout << "\n1.IESIRE     --PENTRU A IESI DIN PROGRAM--";
		cout << "\n2.MENIU      --PENTRU A AFISA MENIUL--";
		cout << "\n3.RETETAR    --PENTRU A AFISA O ANUMITA RETETA--";
		cout << "\n4.COMANDA    --PENTRU A FACE O COMANDA--";
		cout << "\n5.VEGANE     --PENTRU A VIZUALIZA PREPARATELE VEGANE--";
		cout << "\n6.PRETURI    --PENTRU A VIZUALIZA CEL MAI SCUMP/IEFTIN PREPARAT--";
		cout << "\n7.EXTRA      --PENTRU UN TOPPING EXTRA PE PREPARATUL ALES--";
		cout << "\n8.CALORII    --PENTRU A VIZUALIZA NUMARUL DE CALORII PENTRU FIECARE PREPARAT--";
		cout << "\n9.PRELUCRARI --PENTRU DIFERITELE PRELUCRARI DIN CLASELE EXISTENTE--";
		
		cout << endl;
		cout << "\nINTRODUCETI COMANDA PE CARE DORITI SA O EXECUTATI:\n";
		cin >> optiune;
		if (optiune == "MENIU")
		{
			cout << m;
			continue;
		}
		if (optiune == "RETETAR")
		{
			bool exista1 = false;
			cout << "\nPreparate: ";
			cout << endl;
			for (int i = 0; i < nr_total_preparate; i++)
			{
				cout << endl;
				cout << meniu[i] << "\n";
			}
			cout << endl;
			cout << "\nINTRODUCETI IN ACEST FORMAT !"<<"\n";
			cout << "\nIntroduceti preparatul pentru care doriti lista cu ingrediente: ";
			cin >> ws;
			getline(cin, preparat);
			for (int i = 0; i < nr_total_preparate; i++)
			{
				if (meniu[i] == preparat)
				{
					exista1 = true;
					r.afiseazaRetete(preparat);
				}
			}
			if (exista1 == false)
				cout << "\nDenumire gresita sau nu exista preparatul";
			continue;
		}
		if (optiune == "COMANDA")
		{
			float suma = 0;
			int comanda = 0;
			string* comenzi = nullptr;
			bool adaugaComanda= true;
			while (adaugaComanda)
			{
				cout << "\nPreparate: ";
				cout << endl;
				for (int i = 0; i < nr_total_preparate; i++)
				{
					cout << endl;
					cout << meniu[i] << "\n";
				}
				cout << "\nIntroduceti preparatul pentru care doriti sa il comandati: ";
				cin >> ws;
				getline(cin, preparat);
				bool exista = false;
				for (int i = 0; i < nr_total_preparate; i++)
				{
					if (meniu[i] == preparat)
					{
						exista = true;
						cout << "\nCe cantitate? ";
						cin >> cantitate; 
						bool adaugata= listaRetete[i].CalculeazaCantitate(preparat, cantitate, listaMateriiPrima);
						if (adaugata == true)
						{
							suma+= r.Reducere(40, preparat, cantitate);
							comanda++;
							string* vector = new string[comanda];
							for (int pozitie = 0; pozitie < comanda-1; pozitie++)
							{
								vector[pozitie] = comenzi[pozitie];
							}
							vector[comanda-1] = meniu[i];
							delete[] comenzi;
							comenzi = vector;
							
						}
					}
				}
				
				if(exista==false)
					cout << "\nDenumire gresita sau nu exista preparatul";
				cout << endl;
				cout << "\nDoriti sa adaugati alt preparat in comanda? (da/nu): ";
				string nou;
				cin >> nou;
				if (nou == "da" || nou=="DA" || nou=="Da");
				{
					adaugaComanda = true;
					optiune = "COMANDA";
				}
				if (nou == "nu" || nou=="NU" ||nou=="Nu")
				{
					adaugaComanda = false;
					cout << "\nComanda finala: \n";
					for (int i = 0; i < comanda; i++)
					{
						cout <<comenzi[i]<<"\n";
					}
					cout <<"\nSuma totala: " << suma<<" lei ";
				}
			}
			
		}
		if (optiune == "VEGANE")
		{
			//OPERATOR []
			string* vegane = m["vegana"];
			cout << "\nPreparate vegane: ";
			cout << endl;
			for (int i = 0; i < m.getPreparateVegane(); i++)
			{
				cout << "\n" << vegane[i] << " ";
			}
		}
		if (optiune == "PRETURI")
		{
			Preparate::pretMax(lista_preparate, nr_total_preparate);
			Preparate::pretMin(lista_preparate, nr_total_preparate);
		}
		if (optiune == "EXTRA")
		{
			bool exista2 = false;
			string topping;
			cout << "\nTopping extra pentru: PASTE / PIZZA? (+10 lei/Topping)\n";
			cin >> ws;
			getline(cin, topping);
			if (topping == "PIZZA")
			{
				exista2 = true;
				cout << "\nPizza: " << endl;
				for (int i = 0; i < nr_total_preparate / 2; i++)
				{
					cout << pizza[i].getDenumirePreparat() << "\n";
				}
				bool exista4 = false;
				string preparat1;
				cout << "\nPentru ce preparat doriti topping-ul extra?\n";
				cin >> ws;
				getline(cin, preparat1);
				bool exista3 = false;
				cout << "\nAlege un topping: ";
				cout << "\n1.Sos dulce";
				cout << "\n2.Sos iute";
				cout << "\n3.Sos alb";
				char* extra;
				string buffer;
				cout << endl;
				cout << "\nCe topping extra doriti?\n";
				cin >> ws;
				getline(cin, buffer);
				extra = new char[buffer.size() + 1];
				strcpy(extra, buffer.data());

				if (strcmp(extra, "Sos dulce") == 0 || strcmp(extra, "Sos iute") == 0 || strcmp(extra, "Sos alb") == 0)
				{
					exista3 = true;
					for (int i = 0; i < nr_total_preparate / 2; i++)
					{
						if (pizza[i].getDenumirePreparat() == preparat1)
						{
							exista4 = true;
							p11 = pizza[i] + extra;
							cout << p11;
						}
					}
					if (exista4 == false)
						cout << "\nDenumire preparat gresita sau nu exista preparatul";
				}
				if (exista3 == false)
					cout << "\nDenumire topping gresita sau nu exista toppingul";
			}
			if (topping == "PASTE")
			{
				exista2= true;
				cout << "\nPaste: " << endl;
				for (int i = 0; i < nr_total_preparate / 2; i++)
				{
					cout << paste[i].getDenumirePreparat() << "\n";
				}
				bool exista5 = false;
				string preparat1;
				cout << "\nPentru ce preparat doriti topping-ul extra?\n";
				cin >> ws;
				getline(cin, preparat1);
				bool exista4 = false;
				cout << "\nAlege un topping: ";
				cout << "\n1.Cheddar";
				cout << "\n2.Pecorino";
				cout << "\n3.Arrabbiata";
				char* extra;
				string buffer;
				cout << endl;
				cout << "\nCe topping extra doriti?\n";
				cin >> ws;
				getline(cin, buffer);
				extra = new char[buffer.size() + 1];
				strcpy(extra, buffer.data());

				if (strcmp(extra, "Cheddar") == 0 || strcmp(extra, "Pecorino") == 0 || strcmp(extra, "Arrabbiata") == 0)
				{
					exista4= true;
					for (int i = 0; i < nr_total_preparate / 2; i++)
					{
						bool exista6 = false;
						if (paste[i].getDenumirePreparat() == preparat1)
						{
							exista5= true;
							p11 = paste[i] + extra;
							cout << p11;
						}

					}
					if (exista5 == false)
						cout << "\nDenumire preparat gresita sau nu exista preparatul";
				}
				if (exista4 == false)
					cout << "\nDenumire topping gresita sau nu exista toppingul";
			}
			if (exista2 == false)
				cout << "\nIntroduceti in formatul PASTE sau PIZZA !";

		}
		if (optiune == "CALORII")
		{
			for (int i = 0; i < nr_total_preparate; i++)
			{
				cout<<"\nCalorii pentru produsul "<<lista_preparate[i].getDenumirePreparat()<<" : "<<listaRetete[i].afisareCalorii(preparat, nrCalorii, listaMateriiPrima)<<" calorii .";
				
			}
			
		}
		if (optiune == "PRELUCRARI")
		{
			cout << endl << "\nCLASA 1";
			cout << "\nGET SI SET";
			cout << "\nDenumirea initiala a preparatului 6: " << p6.getDenumirePreparat();
			p6.setDenumirePreparat("Pizza Margherita (Clasica)");
			cout << "\nDenumirea preparatului 6: " << p6.getDenumirePreparat();
			cout << "\nPret initial preparat 6: " << p6.getPret();
			p6.setPret(32);
			cout << "\nPret preparat 6: " << p6.getPret();
			cout << "\nAtribut static";
			cout << " - Numarul total de preparate: " << nr_total_preparate;
			cout << endl;
			cout <<"\nCLASA 2";
			cout << "\nMetoda 1 afisare:";
			m.afisareMeniu();
			cout << endl;
			cout << "\nCLASA 3";
			cout << "\nAtribut static:";
			cout << "\nNr materii prime:" << nrMateriiPrime;
			//postincrementare
			cout << "\nOperator++";
			m2 = m3++;
			cout << m2 << m3;
			//preincrementare
			m4 = ++m5;
			cout << m4 << m5;
			cout << "\nMetoda afisare clasa 3:";
			cout<<"\nMateria prima care are stocul cel mai mic: " << MateriePrima::afisareStocCelMaiMic(listaMateriiPrima);
			cout << "\nMateria prima care are stocul cel mai mare: " << MateriePrima::afisareStocCelMaiMare(listaMateriiPrima);
			cout << endl;
			cout << "\nCLASA 4";
			cout << endl;
			cout << "\noperator ==";
			if (p1 == p2)
				cout << "\nPretul preparatului 1 este = cu pretul preparatului 2";
			else
				cout << "\nPretul preparatului 1 nu este = cu pretul preparatului 2";
			//operator!
			cout << endl;
			cout << "\nOperator ! ";
			if (!m2)
			{
				cout << "\nMateria prima 1 este diferita de 0";
			}
			else
				cout << "\nMateria prima 1 nu este diferita de 0";
		}
		if(optiune!="MENIU" && optiune!="RETETAR" && optiune!="IESIRE" && optiune!="COMANDA" && optiune!="VEGANE" && optiune!="PRETURI" && optiune!="EXTRA" && optiune!="PRELUCRARI" && optiune!="CALORII")
		    cout << "\nOPTIUNE INVALIDA, INTRODUCETI O OPTIUNE VALIDA\n"; 
	} while (optiune != "IESIRE");
		
	return 0;
}