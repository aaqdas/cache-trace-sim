import sys
import os

def main():
    if len(sys.argv) < 2:
        print("Usage: python valgrind_to_trace.py <input_trace> [output_file]")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else "converted_trace.txt"

    if not os.path.isfile(input_file):
        print(f"Error: File '{input_file}' not found.")
        sys.exit(1)

    uop_id = 1
    current_pc = None

    with open(input_file, 'r') as fin, open(output_file, 'w') as fout:
        # Write header line
        fout.write(
            "Uop\tPC\tSrc1\tSrc2\tDest\tFlags\tBranch\tLd/St\tImmediate\tMem. Address\tFallthrough PC\tTarget PC\tMacro Opcode\tMicro Opcode\n"
        )

        for line in fin:
            line = line.strip()
            if not line or line.startswith("=="):
                continue  # Skip empty and Valgrind metadata lines

            try:
                tokens = line.split()
                if len(tokens) < 2:
                    continue  # Ignore malformed lines

                op_type = tokens[0]
                addr_info = tokens[1]

                # Parse address and size fields
                if ',' in addr_info:
                    addr_str, size_str = addr_info.split(',')
                else:
                    addr_str, size_str = addr_info, '0'

                # Normalize address string, keep leading zeros removed but allow '0'
                addr = addr_str.lstrip('0') or '0'
                size = size_str

                if op_type == 'I':
                    # Instruction fetch - update current PC
                    current_pc = addr
                elif op_type in ['L', 'S', 'M']:
                    if current_pc is None:
                        # No instruction PC available yet, skip
                        continue

                    # Expand 'M' (Modify) into Load + Store
                    ops_to_emit = ['L', 'S'] if op_type == 'M' else [op_type]

                    for mem_op in ops_to_emit:
                        ld_st = 'L' if mem_op == 'L' else 'S'
                        macro = 'LOAD' if ld_st == 'L' else 'STORE'

                        fout.write(
                            f"{uop_id}\t{current_pc}\t-1\t-1\t-1\t-\t-\t{ld_st}\t{size}\t{addr}\t0\t0\t{macro}\t{mem_op}\n"
                        )
                        uop_id += 1

                else:
                    # Unknown operation type, skip or optionally handle here
                    continue

            except Exception as e:
                print(f"Warning: Skipping line due to parse error: {line}")
                print(f"Reason: {e}")
                continue

    print(f"✅ Converted trace saved to: {output_file}")


if __name__ == "__main__":
    main()
