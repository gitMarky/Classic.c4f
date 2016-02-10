#appendto Goal_ResourceExtraction

public func SetResource(string resource, int percent)
{
	percent = percent ?? 100;

	var pos = GetLength(resource_list);
	resource_list[pos] = resource;
	var mat_cnt = GetMaterialCount(Material(resource)) * percent / 100;
	var blast_ratio = GetMaterialVal("Blast2ObjectRatio", "Material", Material(resource));
	tolerance_list[pos] = Max(1, mat_cnt / blast_ratio / 20);
	return;
}
