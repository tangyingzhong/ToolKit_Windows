///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Load modules in the plugin under bin directory
///</describe>
/// <date>2019/9/2</date>
///***********************************************************************
#ifndef MODULELOADER_H
#define MODULELOADER_H

template<class T>
class ModuleLoader
{
public:
	typedef DllLoader* Loader;
	typedef T* PluginInterface;
	typedef PluginInterface(*CreateModule)();
	typedef None(*DestoryModule)(PluginInterface);

public:
	// Construct the ModuleLoader
	ModuleLoader(String strModuleFilePath) :m_strModuleName(_T("")),
		m_strModuleFilePath(strModuleFilePath),
		m_pDllLoader(NULL),
		m_pPluginInterface(NULL),
		m_pDestoryModule(NULL),
		m_bDisposed(false)
	{
		Initialize();
	}

	// Detructe the ModuleLoader
	~ModuleLoader()
	{
		Destory();
	}

private:
	// Forbid the Copy ModuleLoader
	ModuleLoader(const ModuleLoader& other) {	}

	// Forbid the assigment of ModuleLoader
	ModuleLoader& operator=(const ModuleLoader& other) {	}

public:
	// Get module interface 
	T* GetModuleInterface() const
	{
		return GetPluginInterface();
	}

	// Get the ModuleName
	inline String GetModuleName() const
	{
		return m_strModuleName;
	}

private:
	// Load the module
	Boolean Load()
	{
		if (GetDllLoader() == NULL)
		{
			return false;
		}

		if (GetModuleFilePath().IsEmpty())
		{
			return false;
		}

		if (!IsLoad())
		{
			String strErrorMsg = _T("");

			if (!GetDllLoader()->Load(GetModuleFilePath(), strErrorMsg))
			{
				return false;
			}

			CreateModule pCreateModule = GetDllLoader()->GetFunc<CreateModule>(_T("CreateModule"));
			if (pCreateModule == NULL)
			{
				return false;
			}

			SetCreateModule(pCreateModule);

			SetDestoryModule(GetDllLoader()->GetFunc<DestoryModule>(_T("DestoryModule")));
			if (GetDestoryModule() == NULL)
			{
				return false;
			}

			CreateTheModule();
		}

		return true;
	}

	// Unload the module
	Boolean Unload()
	{
		if (GetDllLoader() == NULL)
		{
			return false;
		}

		if (IsLoad())
		{
			DestoryTheModule();

			return GetDllLoader()->Unload();
		}

		return true;
	}

	// Is load the module
	Boolean IsLoad()
	{
		if (GetDllLoader() == NULL)
		{
			return false;
		}

		return GetDllLoader()->IsOpen();
	}

	// Create module
	None CreateTheModule()
	{
		if (GetCreateModule())
		{
			PluginInterface pInterface = (PluginInterface)m_pCreateModule();

			SetModuleInterface(pInterface);
		}
	}

	// Destory module
	None DestoryTheModule()
	{
		if (GetDestoryModule())
		{
			m_pDestoryModule(GetModuleInterface());
		}
	}

	// Set module interface
	None SetModuleInterface(PluginInterface pInterface)
	{
		SetPluginInterface(pInterface);
	}

	// Configure module name 
	None ConfigureModuleName()
	{
		if (GetModuleFilePath().IsEmpty())
		{
			SetModuleName(_T(""));

			return;
		}

		Int32 iPos = GetModuleFilePath().FindLast(_T("\\"));
		if (iPos == -1)
		{
			SetModuleName(_T(""));

			return;
		}

		String strModuleName = GetModuleFilePath().Right(GetModuleFilePath().GetLength() - iPos - 1);

		SetModuleName(strModuleName);
	}

private:
	// Init the module loader
	None Initialize()
	{
		// Configure the module name
		ConfigureModuleName();

		// Create a dll loader
		CreateDllLoader();

		// Load the module
		Load();
	}

	// Destory the module loader
	None Destory()
	{
		if (!GetDisposed())
		{
			SetDisposed(true);

			// Unload the module
			Unload();

			// Destory the dll loader
			DestoryDllLoader();
		}
	}

	// Create a dll loader
	None CreateDllLoader()
	{
		SetDllLoader(new DllLoader());
	}

	// Destory the dll loader
	None DestoryDllLoader()
	{
		if (GetDllLoader())
		{
			delete GetDllLoader();

			SetDllLoader(NULL);
		}
	}

private:
	// Set the ModuleName
	inline None SetModuleName(String strModuleName)
	{
		m_strModuleName = strModuleName;
	}

	// Get the ModuleFilePath
	inline String GetModuleFilePath() const
	{
		return m_strModuleFilePath;
	}

	// Set the ModuleFilePath
	inline void SetModuleFilePath(String strModuleFilePath)
	{
		m_strModuleFilePath = strModuleFilePath;
	}

	// Get the DllLoader
	inline Loader GetDllLoader() const
	{
		return m_pDllLoader;
	}

	// Set the DllLoader
	inline None SetDllLoader(Loader pDllLoader)
	{
		m_pDllLoader = pDllLoader;
	}

	// Get the PluginInterface
	inline PluginInterface GetPluginInterface() const
	{
		return m_pPluginInterface;
	}

	// Set the PluginInterface
	inline None SetPluginInterface(PluginInterface pPluginInterface)
	{
		m_pPluginInterface = pPluginInterface;
	}

	// Get the CreateModule
	inline CreateModule GetCreateModule() const
	{
		return m_pCreateModule;
	}

	// Set the CreateModule
	inline None SetCreateModule(CreateModule pCreateModule)
	{
		m_pCreateModule = pCreateModule;
	}

	// Get the DestoryModule
	inline DestoryModule GetDestoryModule() const
	{
		return m_pDestoryModule;
	}

	// Set the DestoryModule
	inline None SetDestoryModule(DestoryModule pDestoryModule)
	{
		m_pDestoryModule = pDestoryModule;
	}

	// Get disposed status
	inline Boolean GetDisposed() const
	{
		return m_bDisposed;
	}

	// Set the disposed status
	inline None SetDisposed(Boolean bDisposed)
	{
		m_bDisposed = bDisposed;
	}

private:
	// Module name
	String m_strModuleName;

	// Module file path
	String m_strModuleFilePath;

	// Dll loader
	Loader m_pDllLoader;

	// Module interface
	PluginInterface m_pPluginInterface;

	// Create func
	CreateModule m_pCreateModule;

	// Destory func
	DestoryModule  m_pDestoryModule;

	// Disposed status
	Boolean m_bDisposed;
};
#endif //MODULELOADER_H


