#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include<vector> 
#include<list>
#include <set>
#include<map>
#include <sstream>


using namespace std;
//interfata
class IFile
{
	virtual void saveToFile(fstream& file) = 0;
	virtual void restoreFromFile(fstream& file) = 0;
};
//clasa Preparat
class Preparat : public IFile
{
	const int id_preparat;
	char* denumire_preparat = nullptr;
	float pret = 0;
	static int nr_preparate;

public:
	Preparat() :id_preparat(id_preparat)
	{

	}

	//constructor cu parametrii 1
	Preparat(int id_preparat) :id_preparat(id_preparat)
	{

	}

	//constructor cu parametrii 2
	Preparat(int id_preparat, const char* denumire_preparat, float pret) :id_preparat(id_preparat)
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
	Preparat(const Preparat& m) :id_preparat(m.id_preparat)
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
	Preparat& operator=(const Preparat& m)
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
	friend ostream& operator<<(ostream& out, const Preparat& m)
	{
		out << "\n----------------------------------";
		if (m.denumire_preparat != nullptr && strlen(m.denumire_preparat) >= 3)
		{
			out << "\nDenumire preparat: " << m.denumire_preparat;
		}
		else
			out << "\nDenumire preparat: -";
		out << "\nPretul preparatului: " << m.pret << " lei ";
		out << "\n----------------------------------";
		return out;
	}

	
	virtual void restoreFromFile(fstream& file)
	{
		int lg;
		file.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		file.read(buffer, lg);
		this->denumire_preparat = new char[strlen(buffer) + 1];
		strcpy(this->denumire_preparat, buffer);
		delete[] buffer;
		file.read((char*)&this->pret, sizeof(float));
	}
	virtual void saveToFile(fstream& file)
	{
		int lg = strlen(this->denumire_preparat) + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->denumire_preparat, lg);
		file.write((char*)&this->pret, sizeof(float));
	}
	//operator << OFSTREAM
	friend ofstream& operator<<(ofstream& out, const Preparat& m)
	{
		if (m.denumire_preparat != nullptr && strlen(m.denumire_preparat) >= 3)
		{
			out <<  m.denumire_preparat<<'\n';
		}
		else
			out << "-";
		out << m.pret<< '\n';
		return out;
	}
	
	//operator >>
	friend istream& operator>>(istream& in, Preparat& m)
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
	//operator >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, Preparat& m)
	{
		delete[] m.denumire_preparat;
		m.denumire_preparat = nullptr;
		in >> ws;
		string buffer;
		getline(in, buffer);
		m.denumire_preparat = new char[buffer.size() + 1];
		strcpy(m.denumire_preparat, buffer.data());
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
		return Preparat::nr_preparate;
	}
	static void setNrPreparate(int nrPreparate)
	{
		if (nrPreparate > 0)
		{
			Preparat::nr_preparate = nrPreparate;
		}
	}
	//operator cast
	explicit operator float()
	{
		return this->pret;
	}
	

	//operator ==
	bool operator==(const Preparat& p)
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
	static float pretMax(Preparat* preparate, int nr_preparate)
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
			
			return max;
		}
	}
	//metoda de afisare 2
	static float pretMin(Preparat* preparate, int nr_preparate)
	{
		if (nr_preparate > 0 && preparate != nullptr)
		{
			float min = preparate[0].getPret();
			string denumire = preparate[0].getDenumirePreparat();
			for (int i = 0; i < nr_preparate; i++)
			{
				float pret = (float)preparate[i];
				if (min > pret)
				{
					min = pret;
					denumire = preparate[i].getDenumirePreparat();
				}
			}
			return min;
		}
	}

	//destructor
	~Preparat()
	{
		delete[] this->denumire_preparat;
		this->denumire_preparat = nullptr;
	}
	static bool gasesteInFisierPreparat(string preparate, string preparat_cautat)
	{
		ifstream fisier(preparate.c_str());
		string linie;
		while (getline(fisier, linie))
		{
			if (linie.find(preparat_cautat) != -1)
			{
				fisier.close();
				return true;
			}
		}
		fisier.close();
	}
	static int numarPreparate(string preparate)
	{
		ifstream fisier(preparate.c_str());
		int contor = 0;
		int contor1 = 0;
		string linie;
		while (getline(fisier, linie))
		{
			contor++;

		}
		contor1 = contor / 2;
		fisier.close();
		return contor1;

	}

	float suma_totala(string preparate,string preparat,int cantitateDorita)
	{
		float suma = 0;
		string linie1;
		bool gasit = 0;
		ifstream fisier_preparate(preparate.c_str());
		
				while (getline(fisier_preparate, linie1))
				{
					if (gasit == 0)
					{
						if (linie1==preparat)
						{
							while (getline(fisier_preparate, linie1))
							{
								gasit = 1;
								suma = stof(linie1) * cantitateDorita;
								cout << "\nPret total: " << suma << " lei ";
								return suma;
								break;
							}

						}
					}
				}
		
		fisier_preparate.close();
	}
	//PENTRU SET
	friend bool operator<(const Preparat& p1, const Preparat& p2)
	{
		return p1.pret < p2.pret;
	}
	
	void readFromCSVFile(fstream& f)
	{
		string linie;
		if (f.is_open())
		{
			getline(f, linie);
			stringstream s(linie);

			delete[] this->denumire_preparat;
			this->denumire_preparat = nullptr;
			string buffer;
			getline(s, buffer, ';');
			this->denumire_preparat = new char[buffer.size() + 1];
			strcpy(this->denumire_preparat, buffer.data());
			s >> this->pret;
		}
	}
	
};
int Preparat::nr_preparate = 0;

//clasa 2
class Meniu : public IFile
{
	Preparat* preparate = nullptr;
	int nrProduseMeniu = 0;

public:
	Meniu()
	{

	}

	//constructor cu parametrii 1
	Meniu(Preparat* preparate, int nrProduseMeniu)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparat[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = preparate[i];
			}
		}
	}

	//constructor de copiere
	Meniu(const Meniu& m)
	{
		if (m.nrProduseMeniu > 0 && m.preparate != nullptr)
		{
			this->nrProduseMeniu = m.nrProduseMeniu;
			this->preparate = new Preparat[this->nrProduseMeniu];
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
				this->preparate = new Preparat[this->nrProduseMeniu];
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
			out << "\nDenumire preparat: " << m.preparate[i].getDenumirePreparat() << "\nPretul preparatului: " << m.preparate[i].getPret() << " lei " << endl;
		}
		out << "\n--------------------------";
		return out;
	}

	//operator << OFSTREAM
	friend ofstream& operator<<(ofstream& out, const Meniu& m)
	{
		out << m.nrProduseMeniu<<'\n';
		out << endl;
		
		for (int i = 0; i < m.nrProduseMeniu; i++)
		{
			out << m.preparate[i].getDenumirePreparat() << '\n' << m.preparate[i].getPret() <<  endl;
		}
		return out;
	}
	virtual void saveToFile(fstream& file)
	{
		file.write((char*)&this->nrProduseMeniu, sizeof(int));
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			preparate[i].saveToFile(file);
		}
	}
	virtual void restoreFromFile(fstream& file)
	{
		file.read((char*)&this->nrProduseMeniu, sizeof(int));
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			preparate[i].restoreFromFile(file);
		}
	}
	//operator >>
	friend istream& operator>>(istream& in, Meniu& m)
	{

		delete[] m.preparate;
		m.preparate = nullptr;
		cout << "\nIntroduceti numarul de produse din meniu: ";
		in >> m.nrProduseMeniu;
		m.preparate = new Preparat[m.nrProduseMeniu];
		for (int i = 0; i < m.nrProduseMeniu; i++)
		{
			cout << "\nIntroduceti informatiile pentru preparatul " << i + 1 << " : ";
			in >> m.preparate[i];
		}
		return in;
	}

	//operator >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, Meniu& m)
	{

		delete[] m.preparate;
		m.preparate = nullptr;
		in >> m.nrProduseMeniu;
		m.preparate = new Preparat[m.nrProduseMeniu];
		for (int i = 0; i < m.nrProduseMeniu; i++)
		{
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

	

	//metoda afisare 2
	string* operator[](const char* vegana)
	{
		if (this->preparate != nullptr && this->nrProduseMeniu > 0)
		{
			int nr = 0;
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				if (strstr(preparate[i].getDenumirePreparat(), vegana))
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
	//STRUCTURA LISTA
	void afisare_vegan()
	{
		list<string> IComenzi;
		string* vegane = operator[]("vegana");
		for (int i = 0; i < getPreparateVegane(); i++)
		{
			IComenzi.push_back(vegane[i]);
		}
		cout << "\nPreparate vegane: ";
		cout << endl;
		list<string>::iterator itListComenzi;
		for (itListComenzi = IComenzi.begin(); itListComenzi != IComenzi.end(); itListComenzi++)
			cout << *itListComenzi << endl;
	}
	
	
};

//clasa 3
class MateriePrima : public IFile
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

	//operator<< OFSTREAM
	friend ofstream& operator<<(ofstream& out, const MateriePrima& mp)
	{
		out << mp.denumireMateriePrima<<endl;
		out <<  mp.cantitateMaxima<<endl;
		return out;
	}
	virtual void saveToFile(fstream& file)
	{
		int lg = strlen(this->denumireMateriePrima) + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->denumireMateriePrima, lg);
		file.write((char*)&this->cantitateMaxima, sizeof(float));
	}
	virtual void restoreFromFile(fstream& file)
	{
		int lg;
		file.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		file.read(buffer, lg);
		this->denumireMateriePrima = new char[strlen(buffer) + 1];
		strcpy(this->denumireMateriePrima, buffer);
		delete[] buffer;
		file.read((char*)&this->cantitateMaxima, sizeof(float));
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
	//operator >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, MateriePrima& mp)
	{
		delete[] mp.denumireMateriePrima;
		mp.denumireMateriePrima = nullptr;
		in >> ws;
		string buffer;
		getline(in, buffer);
		mp.denumireMateriePrima = new char[buffer.size() + 1];
		strcpy(mp.denumireMateriePrima, buffer.data());
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
			strcpy(this->denumireMateriePrima, denumire);
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
	
	static int numarMateriiPrime(string materiiPrime)
	{
		ifstream fisier(materiiPrime.c_str());
		int contor = 0;
		int contor1 = 0;
		string linie;
		while (getline(fisier, linie))
		{
			contor++;

		}
		contor1 = contor / 2;
		fisier.close();
		return contor1;

	}
	string proceseaza(string linie)
	{
		
			if (linie.empty() == true)
			{
				delete[] this->denumireMateriePrima;
				this->denumireMateriePrima = new char[linie.size() + 1];
				strcpy(this->denumireMateriePrima, linie.data());
				
			}
			
			return linie;

	}

	
	void setupdateStoc(float cantitateConsumata, string linie)
	{

		this->cantitateMaxima = stof(linie);
		if (cantitateConsumata > 0 && this->cantitateMaxima >= cantitateConsumata) {
			this->cantitateMaxima -= cantitateConsumata;

		}
		else {
			cout << "\n Nu se poate face comanda, nu sunt destule materii prime";
		}

	}
	void readFromCSVFile(fstream& f)
	{
		string linie;
		if (f.is_open())
		{
			getline(f, linie);
			stringstream s(linie);

			delete[] this->denumireMateriePrima;
			this->denumireMateriePrima = nullptr;
			string buffer;
			getline(s, buffer, ';');
			this->denumireMateriePrima = new char[buffer.size() + 1];
			strcpy(this->denumireMateriePrima, buffer.data());
			s >> this->cantitateMaxima;
		}
	}
	
};
int MateriePrima::nrMateriiPrime = 0;

//clasa 4
class Retetar : public IFile
{
	MateriePrima* materiePrima = nullptr;
	Preparat* preparate = nullptr;
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
	Retetar(Preparat* preparate, string* Ingrediente, float* cantitate, int nrProduseMeniu, int nrIngrediente)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparat[this->nrProduseMeniu];
			for (int i = 0; i < this->nrProduseMeniu; i++)
			{
				this->preparate[i] = preparate[i];
			}
		}
		if (nrIngrediente > 0 && Ingrediente != nullptr && cantitate != nullptr)
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
			this->preparate = new Preparat[this->nrProduseMeniu];
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
				this->preparate = new Preparat[this->nrProduseMeniu];
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
					out << r.Ingrediente[i] << " - " << r.cantitate[i] << " grame " << endl;
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

	
	//operator << OFSTREAM
	friend ofstream& operator<<(ofstream& out, const Retetar& r)
	{
		
		for (int i = 0; i < r.nrProduseMeniu; i++)
		{
			out << r.preparate[i].getDenumirePreparat()<<'\n' << r.preparate[i].getPret() << '\n';
			out <<  r.nrIngrediente;
			out << endl;
			if (r.nrIngrediente > 0 && r.Ingrediente != nullptr && r.cantitate != nullptr)
			{
				for (int i = 0; i < r.nrIngrediente; i++)
				{
					out << r.Ingrediente[i] << endl;
					out << r.cantitate[i]<<endl;
				}
			}
			else
			{
				out << " - ";
			}
		}
		
		return out;
	}
	virtual void saveToFile(fstream& file)
	{
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			preparate[i].saveToFile(file);
			file.write((char*)&this->nrIngrediente, sizeof(int));
			if (this->nrIngrediente > 0 && this->Ingrediente != nullptr && this->cantitate != nullptr)
			{
				for (int j = 0; j < this->nrIngrediente; j++)
				{
					int lg =this->Ingrediente[j].length() + 1;
					file.write((char*)&lg, sizeof(int));
					file.write(this->Ingrediente[j].data(), lg);
					file.write((char*)&this->cantitate[j], sizeof(float));
				}
			}
		}
	}
	virtual void restoreFromFile(fstream& file)
	{
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			preparate[i].restoreFromFile(file);
			file.read((char*)&this->nrIngrediente, sizeof(int));
			if (this->nrIngrediente > 0 && this->Ingrediente != nullptr && this->cantitate != nullptr)
			{
				for (int j = 0; j < this->nrIngrediente; j++)
				{
					
					int lg;
					file.read((char*)&lg, sizeof(int));
					char* buffer = new char[lg];
					file.read(buffer, lg);
					this->Ingrediente[j]= buffer;
					delete[] buffer;

					file.read((char*)&this->cantitate[j], sizeof(float));
				}
			}
		}
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
		r.preparate = new Preparat[r.nrProduseMeniu];
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
			cout << "\nIntroduceti denumirea ingredientului " << i + 1 << " : ";
			in >> ws;
			string buffer;
			getline(in, buffer);
			r.Ingrediente[i] = new char[buffer.size() + 1];
			r.Ingrediente[i] = buffer;
			cout << "\nIntroduceti cantitatea necesara " << i + 1 << " : ";
			in >> r.cantitate[i];
		}
		return in;
	}
	//operator >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, Retetar& r)
	{
		
		delete[] r.preparate;
		r.preparate = nullptr;
		delete[] r.Ingrediente;
		r.Ingrediente = nullptr;
		delete[] r.cantitate;
		r.cantitate = nullptr;
		r.nrProduseMeniu = 1;
		r.preparate = new Preparat[r.nrProduseMeniu];
		for (int i = 0; i < r.nrProduseMeniu; i++)
		{
			in >> r.preparate[i];
		}
		in >> r.nrIngrediente;
		r.Ingrediente = new string[r.nrIngrediente];
		r.cantitate = new float[r.nrIngrediente];
		for (int i = 0; i < r.nrIngrediente; i++)
		{
			in >> ws;
			string buffer;
			getline(in, buffer);
			r.Ingrediente[i] = new char[buffer.size() + 1];
			r.Ingrediente[i] = buffer;
			in >> r.cantitate[i];
		}
		return in;
	}
	
	
	bool CalculeazaCantitate(string preparat, int cantitateDorita, string materiiPrime, string preparate,MateriePrima m)
	{
		bool preparatGasit = false;
		int ok = 1;

		if (preparat.size() >= 3 && cantitateDorita > 0)
		{
			ifstream fisier(materiiPrime.c_str());
			
			if (Preparat::gasesteInFisierPreparat(preparate, preparat))
			{
			
				preparatGasit = true;
				float* cantitate_necesara = new float[this->nrIngrediente];
				for (int k = 0; k < this->nrIngrediente; k++)
				{
					cantitate_necesara[k] = this->cantitate[k] * cantitateDorita;
				}
				
				for (int j = 0; j < MateriePrima::numarMateriiPrime(materiiPrime); j++)
				{
					string linie;
					while (getline(fisier, linie))
					{

						for (int k = 0; k < this->nrIngrediente; k++)
						{

							if (this->Ingrediente[k] == materiePrima[j].proceseaza(linie))
							{
								while (getline(fisier, linie))
								{
									int cantmax = stof(linie);
									if (cantitate_necesara[k] > cantmax)
									{
										ok = 0;
										break;
									}
									
									break;
								}


							}

						}
					}

				}
				ofstream r1("raport_materie_prima_folosita.txt", fstream::app);
				if (ok == 1)
				{
					fisier.clear();
					fisier.seekg(0, SEEK_SET);
					r1 << "Pentru " << preparat << " -  " << cantitateDorita << " avem nevoie de: " << endl;
					for (int j = 0; j < MateriePrima::numarMateriiPrime(materiiPrime); j++)
					{
						string linie;
						while (getline(fisier, linie))
						{
							for (int k = 0; k < this->nrIngrediente; k++)
							{

								if (this->Ingrediente[k] == materiePrima[j].proceseaza(linie))
								{
									r1 << materiePrima[j].proceseaza(linie) << " - ";
									while (getline(fisier, linie))
									{
										int cantmax = stof(linie);
										r1<< cantitate_necesara[k];
										r1 << endl;
										m.setupdateStoc(cantitate_necesara[k],linie);
										break;
									}
									
								}
							}
						}
					}

				}fisier.close();
				r1.close();
			}
		
			



		}
		
		if (ok == 1 && preparatGasit == true)
		{

			cout << "\nComanda este gata in " << 11 * cantitateDorita << " minute !";
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
	void setIngrediente(int nrIngrediente, string* Ingrediente, float* cantitate)
	{
		if (nrIngrediente > 0 && Ingrediente != nullptr && cantitate != nullptr)
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
class Restaurant_Italian:public IFile
{
	Preparat* preparate = nullptr;
	int nrProduseMeniu = 0;
	Retetar* retete = nullptr;
public:
	Restaurant_Italian()
	{

	}

	//constructor cu parametrii 1
	Restaurant_Italian(Preparat* preparate, Retetar* retete, int nrProduseMeniu)
	{
		if (nrProduseMeniu > 0 && preparate != nullptr)
		{
			this->nrProduseMeniu = nrProduseMeniu;
			this->preparate = new Preparat[this->nrProduseMeniu];
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
			this->preparate = new Preparat[this->nrProduseMeniu];
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
		out << "\nNumar preparate: " << ri.nrProduseMeniu;
		for (int i = 0; i < ri.nrProduseMeniu; i++)
		{
			out << ri.retete[i] << endl;
		}

		return out;
	}

	//operator << OFSTREAM
	friend ofstream& operator<<(ofstream& out, const Restaurant_Italian& ri)
	{
		out <<  ri.nrProduseMeniu<<'\n';
		for (int i = 0; i < ri.nrProduseMeniu; i++)
		{
			out << ri.retete[i];
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
			cout << "\nIntroduceti informatiile legate de restaurant pentru produsul " << i + 1 << " : ";
			in >> ri.retete[i];
		}
		return in;

	}
	virtual void saveToFile(fstream& file)
	{
		file.write((char*)&this->nrProduseMeniu, sizeof(int));
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			retete[i].saveToFile(file);
		}
	}
	virtual void restoreFromFile(fstream& file)
	{
		file.read((char*)&this->nrProduseMeniu, sizeof(int));
		for (int i = 0; i < this->nrProduseMeniu; i++)
		{
			retete[i].restoreFromFile(file);
		}
	}
	//operator >> IFSTREAM
	friend ifstream& operator>>(ifstream& in, Restaurant_Italian& ri)
	{
		delete[] ri.retete;
		ri.retete = nullptr;
		in >> ri.nrProduseMeniu;
		ri.retete = new Retetar[ri.nrProduseMeniu];
		for (int i = 0; i < ri.nrProduseMeniu; i++)
		{
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
				this->preparate = new Preparat[this->nrProduseMeniu];
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

	//destructor
	~Restaurant_Italian()
	{
		delete[] this->preparate;
		this->preparate = nullptr;
		delete[] this->retete;
		this->retete = nullptr;
	}
};

//cd C:\PROBLEME POO\[Proiect][1053][Dulica Georgiana Denisa]-[Faza 1]\x64\Debug
//"C:\PROBLEME POO\[Proiect][1053][Dulica Georgiana Denisa]-[Faza 1]\x64\Debug\[Proiect][1053][Dulica Georgiana Denisa]-[Faza 1].exe" meniu.txt restaurant_italian.txt retetar.txt materiiPrime.txt preparate.txt
int main(int argc, char* argv[])
{


	if (argc ==6)
	{
		Preparat p[10];
		Meniu mm;
		//meniu.txt
		ifstream f(argv[1]);
		f >> mm;
		f.close();
		//restaurant_italian.txt
		ifstream f4(argv[2]);
		int numar_preparate = 0;
		f4 >> numar_preparate;
		//retetar.txt
		ifstream f3(argv[3]);
		//materiiPrime.txt
		ifstream f5(argv[4]);
		ifstream f6(argv[5]);


		Preparat p1(1, "Spaghetti Bolognese", 35);
		Preparat p2(2, "Penne Carbonara", 37);
		Preparat p3(3, "Linguine alle Vongole", 45);
		Preparat p4(4, "Fettuccine Alfredo", 39);
		Preparat p5(5, "Pasta vegana alla Norma", 40);
		Preparat p6(6, "Pizza Margherita", 30);
		Preparat p7(7, "Pizza Pepperoni", 33);
		Preparat p8(8, "Pizza Quattro Formaggi", 41);
		Preparat p9(9, "Pizza vegana", 42);
		Preparat p10(10, "Pizza Diavola", 34);

		Preparat lista_preparate[] = { p1,p2,p3,p4,p5,p6,p7,p8,p9,p10 };
		int nr_total_preparate = Preparat::getNrPreparate();
		string meniu[] = { "Spaghetti Bolognese","Penne Carbonara",  "Linguine alle Vongole" ,"Fettuccine Alfredo","Pasta vegana alla Norma", "Pizza Margherita",  "Pizza Pepperoni" ,"Pizza Quattro Formaggi" ,"Pizza vegana" ,"Pizza Diavola" };


		string optiune;
		string preparat;
		int cantitate;
		map<string, int> mapOptiune;
		do
		{
			cout << endl;
			cout << "\nINTRODUCETI IN ACEST FORMAT !" << "\n";
			cout << "\n1.IESIRE                --PENTRU A IESI DIN PROGRAM--";
			cout << "\n2.MENIU                 --PENTRU A AFISA MENIUL--";
			cout << "\n3.RETETAR               --PENTRU A AFISA O ANUMITA RETETA--";
			cout << "\n4.COMANDA               --PENTRU A FACE O COMANDA--";
			cout << "\n5.PRETURI               --PENTRU A VIZUALIZA CEL MAI SCUMP/IEFTIN PREPARAT--";
			cout << "\n6.VEGANE                --PENTRU A VIZUALIZA PREPARATELE VEGANE--";
			cout << "\n7.RAPORT_COMENZI        --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE FIECARE COMANDA PLASATA--";
			cout << "\n8.RAPORT_SUMA_COMENZI   --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE SUMA TOTALA PENTRU FIECARE COMANDA--";
			cout << "\n9.RAPORT_STOC_FOLOSIT   --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE STOCUL FOLOSIT PENTRU FIECARE COMANDA--";
			cout << "\n10.RAPORT_DATA_MINING   --PENTRU A VIZUALIZA RAPORTUL DATA MINING--";

			cout << endl;
			cout << "\nINTRODUCETI COMANDA PE CARE DORITI SA O EXECUTATI:\n";
			cin >> optiune;
			if (optiune == "MENIU")
			{
				mapOptiune[optiune]++;
				if (argc > 1)
				{
					cout << mm;
				}
				else
				{
					for (int i = 0; i < 10; i++)
						cout << p[i];
				}

			}
			if (optiune == "RETETAR")
			{
				mapOptiune[optiune]++;
				bool exista1 = false;
				cout << "\nPreparate: ";
				cout << endl;

				for (int i = 0; i < numar_preparate; i++)
				{
					cout << endl;
					cout << meniu[i] << "\n";
				}
				cout << endl;
				cout << "\nINTRODUCETI IN ACEST FORMAT !" << "\n";
				cout << "\nIntroduceti preparatul pentru care doriti lista cu ingrediente: ";
				cin >> ws;
				getline(cin, preparat);
				for (int i = 0; i < numar_preparate; i++)
				{
					if (meniu[i] == preparat)
					{
						exista1 = true;
						string denumire;
						while (getline(f4, denumire))
						{
							if (denumire.find(preparat) != -1)
							{
								int pos = f4.tellg();
								int inceput_linie = pos - denumire.length() - 2;
								exista1 = true;
								f4.seekg(inceput_linie, SEEK_SET);
								Retetar reteta;
								f4 >> reteta;
								cout << reteta;
							}

						}

					}

				}
				f4.close();
				if (exista1 == false)
					cout << "\nDenumire gresita sau nu exista preparatul";
				continue;
			}

			if (optiune == "COMANDA")
			{
				mapOptiune[optiune]++;
				float suma = 0;
				int comanda = 0;
				string* comenzi = nullptr;
				bool adaugaComanda = true;
				while (adaugaComanda)
				{
					cout << "\nPreparate: ";
					cout << endl;
					for (int i = 0; i < Preparat::numarPreparate(argv[5]); i++)
					{
						cout << endl;
						cout << meniu[i] << "\n";
					}
					cout << "\nIntroduceti preparatul pentru care doriti sa il comandati: ";
					cin >> ws;
					getline(cin, preparat);
					bool exista = false;
					for (int i = 0; i < Preparat::numarPreparate(argv[5]); i++)
					{
						if (meniu[i] == preparat)
						{
							exista = true;
							cout << "\nCe cantitate? ";
							cin >> cantitate;
							string denumire;
							f3.clear();
							f3.seekg(0, SEEK_SET);
							while (getline(f3, denumire))
							{

								if (denumire.find(preparat) != -1)
								{
									int pos = f3.tellg();
									int inceput_linie = pos - denumire.length() - 2;
									f3.seekg(inceput_linie, SEEK_SET);
									Retetar reteta1;
									f3 >> reteta1;
									MateriePrima m;
									f5 >> m;
									bool adaugata = reteta1.CalculeazaCantitate(preparat, cantitate, argv[4], argv[5], m);
									if (adaugata == true)
									{
										Preparat pp;
										suma += pp.suma_totala(argv[5], preparat, cantitate);
										comanda++;
										string* vector = new string[comanda];
										for (int pozitie = 0; pozitie < comanda - 1; pozitie++)
										{
											vector[pozitie] = comenzi[pozitie];
										}
										vector[comanda - 1] = meniu[i];
										delete[] comenzi;
										comenzi = vector;

									}
								}

							}
						}
					}
					ofstream r("raport_comenzi_plasate.txt", fstream::app);
					ofstream r2("raport_suma_totala_comenzi.txt", fstream::app);
					if (exista == false)
						cout << "\nDenumire gresita sau nu exista preparatul";
					cout << endl;
					cout << "\nDoriti sa adaugati alt preparat in comanda? (da/nu): ";
					string nou;
					cin >> nou;
					if (nou == "da" || nou == "DA" || nou == "Da")
					{
						adaugaComanda = true;
						optiune = "COMANDA";
					}
					if (nou == "nu" || nou == "NU" || nou == "Nu")
					{

						adaugaComanda = false;
						r << "Comanda finala: \n";
						cout << "\nComanda finala: \n";
						for (int i = 0; i < comanda; i++)
						{

							cout << comenzi[i] << "\n";

							r << comenzi[i] << " ";
							r << endl;

						}
						cout << "\nSuma totala: " << suma << " lei ";
						r2 << "Suma totala: " << suma << " lei " << endl;

					}
					r.close();
					r2.close();
				}
				f3.close();
				f5.close();
			}
			if (optiune == "PRETURI")
			{

				mapOptiune[optiune]++;

				set<Preparat> setPreparate;
				setPreparate.insert(p1);
				setPreparate.insert(p2);
				setPreparate.insert(p3);
				setPreparate.insert(p4);
				setPreparate.insert(p5);

				set<Preparat>::iterator itUltimulPreparat;
				itUltimulPreparat = setPreparate.end();
				itUltimulPreparat--;
				cout << "\nCel mai scump preparat din categoria paste este: " << *itUltimulPreparat << endl;
				set<Preparat>::iterator itPrimulPreparat;
				itPrimulPreparat = setPreparate.begin();
				cout << "\nCel mai ieftin preparat din categoria paste este: " << *itPrimulPreparat;

				vector<Preparat> vPreparate;
				vPreparate.push_back(p6);
				vPreparate.push_back(p7);
				vPreparate.push_back(p8);
				vPreparate.push_back(p9);
				vPreparate.push_back(p10);

				Preparat lista_preparate[] = { p6,p7,p8,p9,p10 };
				for (int i = 0; i < vPreparate.size(); i++)
				{
					float pret_max = Preparat::pretMax(lista_preparate, 5);
					if (lista_preparate[i].getPret() >= pret_max)
						cout << "\nCel mai scump preparat din categoria pizza este: " << vPreparate[i] << endl;
				}
				for (int i = 0; i < vPreparate.size(); i++)
				{
					float pret_min = Preparat::pretMin(lista_preparate, 5);
					if (lista_preparate[i].getPret() <= pret_min)
						cout << "\nCel mai ieftin preparat din categoria pizza este: " << vPreparate[i] << endl;
					break;
				}

			}

			if (optiune == "VEGANE")
			{
				mapOptiune[optiune]++;
				Meniu mv(lista_preparate, 10);
				mv.afisare_vegan();


			}
			if (optiune == "RAPORT_COMENZI")
			{
				mapOptiune[optiune]++;
				ifstream r("raport_comenzi_plasate.txt");
				string linie_comanda;
				while (getline(r, linie_comanda))
				{
					cout << linie_comanda << endl;
				}


			}
			if (optiune == "RAPORT_SUMA_COMENZI")
			{
				mapOptiune[optiune]++;
				ifstream r2("raport_suma_totala_comenzi.txt");
				string linie_suma;
				while (getline(r2, linie_suma))
				{
					cout << linie_suma << endl;
				}


			}
			if (optiune == "RAPORT_STOC_FOLOSIT")
			{
				mapOptiune[optiune]++;
				ifstream r1("raport_materie_prima_folosita.txt");
				string linie_stoc;
				int nr = 0;
				while (getline(r1, linie_stoc))
				{

					cout << linie_stoc << endl;

				}
			}
			ofstream r4("raport_data_mining.txt", fstream::out);
			string optiunePopulara;
			int frecventa = 0;
			map<string, int>::iterator itMap;
			for (itMap = mapOptiune.begin(); itMap != mapOptiune.end(); itMap++)
			{
				if (itMap->second > frecventa)
				{
					frecventa = itMap->second;
					optiunePopulara = itMap->first;
				}
			}
			r4 << "\nCea mai folosita optiune de catre utilizator a fost: " << optiunePopulara;
			r4.close();
			if (optiune == "RAPORT_DATA_MINING")
			{
				
				ifstream r4("raport_data_mining.txt");
				string linie_data;
				int nr = 0;
				while (getline(r4, linie_data))
				{

					cout << linie_data << endl;

				}

			}

			if (optiune != "MENIU" && optiune != "RETETAR" && optiune != "IESIRE" && optiune != "COMANDA" && optiune != "PRETURI" && optiune != "VEGANE" && optiune != "RAPORT_COMENZI" && optiune != "RAPORT_SUMA_COMENZI" && optiune != "RAPORT_STOC_FOLOSIT" && optiune != "RAPORT_DATA_MINING")
				cout << "\nOPTIUNE INVALIDA, INTRODUCETI O OPTIUNE VALIDA\n";
		} while (optiune != "IESIRE");

		

	}
	else if (argc == 1)
	{

		Preparat p[10];
		Meniu mm;
		MateriePrima m;
		cout << "\nCitire meniu din CSV sau fisiere BINARE (INTRODUCETI - CSV / BIN -) \n";
		string raspuns;
		cin >> raspuns;
		if (raspuns == "CSV")
		{
			fstream file("Book1.csv", ios::in);
			for (int i = 0; i < 10; i++)
			{
				p[i].readFromCSVFile(file);
			}
			file.close();

			fstream file1("Book2.csv", ios::in);
			for (int i = 0; i < 10; i++)
			{
				m.readFromCSVFile(file1);
			}
			file1.close();
		}
		else if (raspuns == "BIN")
		{
			fstream binar_meniu;
			binar_meniu.open("colectie_preparate.bin");
			if (binar_meniu.is_open())
			{
				for (int i = 0; i < 10; i++)
				{
					p[i].restoreFromFile(binar_meniu);

				}
				binar_meniu.close();
			}
			else
				cout << "\nNu s-a putut deschide";

			fstream binar_materie_prima;
			binar_materie_prima.open("colectie_materiiPrime.bin");
			if (binar_materie_prima.is_open())
			{
				for (int i = 0; i < 10; i++)
				{
					m.restoreFromFile(binar_materie_prima);

				}
				binar_materie_prima.close();
			}
			else
				cout << "\nNu s-a putut deschide";

		}

		Preparat p1(1, "Spaghetti Bolognese", 35);
		Preparat p2(2, "Penne Carbonara", 37);
		Preparat p3(3, "Linguine alle Vongole", 45);
		Preparat p4(4, "Fettuccine Alfredo", 39);
		Preparat p5(5, "Pasta vegana alla Norma", 40);
		Preparat p6(6, "Pizza Margherita", 30);
		Preparat p7(7, "Pizza Pepperoni", 33);
		Preparat p8(8, "Pizza Quattro Formaggi", 41);
		Preparat p9(9, "Pizza vegana", 42);
		Preparat p10(10, "Pizza Diavola", 34);

		Preparat lista_preparate[] = { p1,p2,p3,p4,p5,p6,p7,p8,p9,p10 };
		int nr_total_preparate = Preparat::getNrPreparate();
		string meniu[] = { "Spaghetti Bolognese","Penne Carbonara",  "Linguine alle Vongole" ,"Fettuccine Alfredo","Pasta vegana alla Norma", "Pizza Margherita",  "Pizza Pepperoni" ,"Pizza Quattro Formaggi" ,"Pizza vegana" ,"Pizza Diavola" };

		string optiune;
		string preparat;
		int cantitate;
		map<string, int> mapOptiune;
		do
		{
			cout << endl;
			cout << "\nINTRODUCETI IN ACEST FORMAT !" << "\n";
			cout << "\n1.IESIRE                --PENTRU A IESI DIN PROGRAM--";
			cout << "\n2.MENIU                 --PENTRU A AFISA MENIUL--";
			cout << "\n3.RETETAR               --PENTRU A AFISA O ANUMITA RETETA--";
			cout << "\n4.COMANDA               --PENTRU A FACE O COMANDA--";
			cout << "\n5.PRETURI               --PENTRU A VIZUALIZA CEL MAI SCUMP/IEFTIN PREPARAT--";
			cout << "\n6.VEGANE                --PENTRU A VIZUALIZA PREPARATELE VEGANE--";
			cout << "\n7.RAPORT_COMENZI        --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE FIECARE COMANDA PLASATA--";
			cout << "\n8.RAPORT_SUMA_COMENZI   --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE SUMA TOTALA PENTRU FIECARE COMANDA--";
			cout << "\n9.RAPORT_STOC_FOLOSIT   --PENTRU A VIZUALIZA RAPORTUL CARE CONTINE STOCUL FOLOSIT PENTRU FIECARE COMANDA--";
			cout << "\n10.RAPORT_DATA_MINING   --PENTRU A VIZUALIZA RAPORTUL DATA MINING--";

			cout << endl;
			cout << "\nINTRODUCETI COMANDA PE CARE DORITI SA O EXECUTATI:\n";
			cin >> optiune;
			if (optiune == "MENIU")
			{
				mapOptiune[optiune]++;
				if (argc > 1)
				{
					cout << mm;
				}
				else
				{
					for (int i = 0; i < 10; i++)
						cout << p[i];
				}

			}
			if (optiune == "RETETAR")
			{
				mapOptiune[optiune]++;
				bool exista1 = false;
				cout << "\nPreparate: ";
				cout << endl;
				int numar_preparate = 0;
				ifstream f4("restaurant_italian.txt");
				f4 >> numar_preparate;
				for (int i = 0; i < numar_preparate; i++)
				{
					cout << endl;
					cout << meniu[i] << "\n";
				}
				cout << endl;
				cout << "\nINTRODUCETI IN ACEST FORMAT !" << "\n";
				cout << "\nIntroduceti preparatul pentru care doriti lista cu ingrediente: ";
				cin >> ws;
				getline(cin, preparat);
				for (int i = 0; i < numar_preparate; i++)
				{
					if (meniu[i] == preparat)
					{
						exista1 = true;
						string denumire;
						while (getline(f4, denumire))
						{
							if (denumire.find(preparat) != -1)
							{
								int pos = f4.tellg();
								int inceput_linie = pos - denumire.length() - 2;
								exista1 = true;
								f4.seekg(inceput_linie, SEEK_SET);
								Retetar reteta;
								f4 >> reteta;
								cout << reteta;
							}

						}

					}

				}
				f4.close();
				if (exista1 == false)
					cout << "\nDenumire gresita sau nu exista preparatul";
				continue;
			}

			if (optiune == "COMANDA")
			{
				mapOptiune[optiune]++;
				ifstream f3("retetar.txt");
				float suma = 0;
				int comanda = 0;
				string* comenzi = nullptr;
				bool adaugaComanda = true;
				while (adaugaComanda)
				{
					cout << "\nPreparate: ";
					cout << endl;
					for (int i = 0; i < Preparat::numarPreparate("preparate.txt"); i++)
					{
						cout << endl;
						cout << meniu[i] << "\n";
					}
					cout << "\nIntroduceti preparatul pentru care doriti sa il comandati: ";
					cin >> ws;
					getline(cin, preparat);
					bool exista = false;
					for (int i = 0; i < Preparat::numarPreparate("preparate.txt"); i++)
					{
						if (meniu[i] == preparat)
						{
							exista = true;
							cout << "\nCe cantitate? ";
							cin >> cantitate;
							string denumire;
							f3.clear();
							f3.seekg(0, SEEK_SET);
							while (getline(f3, denumire))
							{

								if (denumire.find(preparat) != -1)
								{
									int pos = f3.tellg();
									int inceput_linie = pos - denumire.length() - 2;
									f3.seekg(inceput_linie, SEEK_SET);
									Retetar reteta1;
									f3 >> reteta1;
									bool adaugata = reteta1.CalculeazaCantitate(preparat, cantitate, "materiiPrime.txt", "preparate.txt", m);
									if (adaugata == true)
									{
										Preparat pp;
										suma += pp.suma_totala("preparate.txt", preparat, cantitate);
										comanda++;
										string* vector = new string[comanda];
										for (int pozitie = 0; pozitie < comanda - 1; pozitie++)
										{
											vector[pozitie] = comenzi[pozitie];
										}
										vector[comanda - 1] = meniu[i];
										delete[] comenzi;
										comenzi = vector;

									}
								}

							}
						}
					}
					ofstream r("raport_comenzi_plasate.txt", fstream::app);
					ofstream r2("raport_suma_totala_comenzi.txt", fstream::app);
					if (exista == false)
						cout << "\nDenumire gresita sau nu exista preparatul";
					cout << endl;
					cout << "\nDoriti sa adaugati alt preparat in comanda? (da/nu): ";
					string nou;
					cin >> nou;
					if (nou == "da" || nou == "DA" || nou == "Da")
					{
						adaugaComanda = true;
						optiune = "COMANDA";
					}
					if (nou == "nu" || nou == "NU" || nou == "Nu")
					{

						adaugaComanda = false;
						r << "Comanda finala: \n";
						cout << "\nComanda finala: \n";
						for (int i = 0; i < comanda; i++)
						{

							cout << comenzi[i] << "\n";

							r << comenzi[i] << " ";
							r << endl;

						}
						cout << "\nSuma totala: " << suma << " lei ";
						r2 << "Suma totala: " << suma << " lei " << endl;

					}
					r.close();
					r2.close();
				}
				f3.close();

			}
			if (optiune == "PRETURI")
			{
				mapOptiune[optiune]++;

				set<Preparat> setPreparate;
				setPreparate.insert(p1);
				setPreparate.insert(p2);
				setPreparate.insert(p3);
				setPreparate.insert(p4);
				setPreparate.insert(p5);

				set<Preparat>::iterator itUltimulPreparat;
				itUltimulPreparat = setPreparate.end();
				itUltimulPreparat--;
				cout << "\nCel mai scump preparat din categoria paste este: " << *itUltimulPreparat << endl;
				set<Preparat>::iterator itPrimulPreparat;
				itPrimulPreparat = setPreparate.begin();
				cout << "\nCel mai ieftin preparat din categoria paste este: " << *itPrimulPreparat;

				vector<Preparat> vPreparate;
				vPreparate.push_back(p6);
				vPreparate.push_back(p7);
				vPreparate.push_back(p8);
				vPreparate.push_back(p9);
				vPreparate.push_back(p10);

				Preparat lista_preparate[] = { p6,p7,p8,p9,p10 };
				for (int i = 0; i < vPreparate.size(); i++)
				{
					float pret_max = Preparat::pretMax(lista_preparate, 5);
					if (lista_preparate[i].getPret() >= pret_max)
						cout << "\nCel mai scump preparat din categoria pizza este: " << vPreparate[i] << endl;
				}
				for (int i = 0; i < vPreparate.size(); i++)
				{
					float pret_min = Preparat::pretMin(lista_preparate, 5);
					if (lista_preparate[i].getPret() <= pret_min)
						cout << "\nCel mai ieftin preparat din categoria pizza este: " << vPreparate[i] << endl;
					break;
				}

			}

			if (optiune == "VEGANE")
			{
				mapOptiune[optiune]++;
				Meniu mv(lista_preparate, 10);
				mv.afisare_vegan();


			}
			if (optiune == "RAPORT_COMENZI")
			{
				mapOptiune[optiune]++;
				ifstream r("raport_comenzi_plasate.txt");
				string linie_comanda;
				while (getline(r, linie_comanda))
				{
					cout << linie_comanda << endl;
				}


			}
			if (optiune == "RAPORT_SUMA_COMENZI")
			{
				mapOptiune[optiune]++;
				ifstream r2("raport_suma_totala_comenzi.txt");
				string linie_suma;
				while (getline(r2, linie_suma))
				{
					cout << linie_suma << endl;
				}


			}
			if (optiune == "RAPORT_STOC_FOLOSIT")
			{
				mapOptiune[optiune]++;
				ifstream r1("raport_materie_prima_folosita.txt");
				string linie_stoc;
				int nr = 0;
				while (getline(r1, linie_stoc))
				{

					cout << linie_stoc << endl;

				}
			}
			ofstream r4("raport_data_mining.txt", fstream::out);
			string optiunePopulara;
			int frecventa = 0;
			map<string, int>::iterator itMap;
			for (itMap = mapOptiune.begin(); itMap != mapOptiune.end(); itMap++)
			{
				if (itMap->second > frecventa)
				{
					frecventa = itMap->second;
					optiunePopulara = itMap->first;
				}
			}
			r4 << "\nCea mai folosita optiune de catre utilizator a fost: " << optiunePopulara;
			r4.close();
			if (optiune == "RAPORT_DATA_MINING")
			{

				ifstream r4("raport_data_mining.txt");
				string linie_data;
				int nr = 0;
				while (getline(r4, linie_data))
				{

					cout << linie_data << endl;

				}

			}
			if (optiune != "MENIU" && optiune != "RETETAR" && optiune != "IESIRE" && optiune != "COMANDA" && optiune != "PRETURI" && optiune != "VEGANE" && optiune != "RAPORT_COMENZI" && optiune != "RAPORT_SUMA_COMENZI" && optiune != "RAPORT_STOC_FOLOSIT" && optiune != "RAPORT_DATA_MINING")
				cout << "\nOPTIUNE INVALIDA, INTRODUCETI O OPTIUNE VALIDA\n";
		} while (optiune != "IESIRE");



	}
    else if (argc != 6 && argc != 1)
    {
	cout << "\nIntroduceti toate fisierele (populare fisiere txt) sau nu introduceti niciunul (populare fisiere binare) !";
    }


}
 

	


	
