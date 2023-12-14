string userInput;

	do
	{
		std::cout << "Enter code of the book:" << std::endl;
		getline(cin, userInput);

		if (CheckIsNumber(userInput))
		{
			m->code = stoi(userInput);
			break;