
/**
 Does a function call with the given parameters on each
 value in an array.
 */
global func CallForEach(array every, function_name)
{
	var results = [];
	RemoveHoles(every);
	for (var each in every)
	{
		PushBack(results, each->Call(function_name, ...));
	}
	return results;
}