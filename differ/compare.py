import xir
import argparse

def load_ops(xmodel_path):
    graph = xir.Graph.deserialize(xmodel_path)
    root = graph.get_root_subgraph()

    # Recursively find leaf subgraph (where real ops are stored)
    def find_leaf_subgraph(subgraph):
        if subgraph.is_leaf:
            return subgraph
        for sg in subgraph.get_children():
            leaf = find_leaf_subgraph(sg)
            if leaf:
                return leaf
        return None

    leaf_subgraph = find_leaf_subgraph(root)
    if not leaf_subgraph:
        print(f"[WARNING] No leaf subgraph found in {xmodel_path}")
        return []

    ops = []
    for op in leaf_subgraph.toposort():
        name = op.get_name()
        op_type = op.get_type()
        shape = op.get_attr("shape") if op.has_attr("shape") else "N/A"
        ops.append((name, op_type, tuple(shape)))
    return ops

def compare_models(model1_path, model2_path):
    ops1 = load_ops(model1_path)
    ops2 = load_ops(model2_path)

    print(f"Loaded {len(ops1)} ops from {model1_path}")
    print(f"Loaded {len(ops2)} ops from {model2_path}")
    print()

    # Check total number of ops
    if len(ops1) != len(ops2):
        print("Number of ops differ!")
        print(f"{model1_path}: {len(ops1)} ops")
        print(f"{model2_path}: {len(ops2)} ops")

    # Compare op-by-op
    for i, (op1, op2) in enumerate(zip(ops1, ops2)):
        name1, type1, shape1 = op1
        name2, type2, shape2 = op2

        if name1 != name2 or type1 != type2 or shape1 != shape2:
            print(f"[Mismatch at op #{i}]")
            print(f"  {model1_path}: name={name1}, type={type1}, shape={shape1}")
            print(f"  {model2_path}: name={name2}, type={type2}, shape={shape2}")
            print()

    # Extra ops (if any)
    if len(ops1) > len(ops2):
        print(f"Extra ops in {model1_path}:")
        for op in ops1[len(ops2):]:
            print(f"  {op}")
    elif len(ops2) > len(ops1):
        print(f"Extra ops in {model2_path}:")
        for op in ops2[len(ops1):]:
            print(f"  {op}")

    print("Comparison complete.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compare two .xmodel structures")
    parser.add_argument("model1", help="Path to first xmodel")
    parser.add_argument("model2", help="Path to second xmodel")
    args = parser.parse_args()

    compare_models(args.model1, args.model2)