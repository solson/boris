module Boris
  INST_CODES = {
    'nop'   => 0,
    'push'  => 1,
    'dup'   => 2,
    'drop'  => 3,
    'swap'  => 4,
    'add'   => 5,
    'print' => 6,
    'halt'  => 7
  }

  class Assembler
    # Convenience method for invoking the assembler on a source code assembly
    # file, returning a bytecode string.
    def self.assemble(source)
      asm = new(source)
      asm.assemble!
      asm.bytecode
    end

    attr_reader :bytecode

    def initialize(source)
      @source = source
    end

    def assemble!
      @bytecode = ""

      @source.split.each do |tok|
        if tok =~ /^\d+$/
          # Stuff the number in as a 32-bit unsigned little-endian integer
          @bytecode << [tok.to_i].pack("V")
        elsif INST_CODES[tok]
          @bytecode << INST_CODES[tok]
        else
          raise "Unrecognized token: #{tok}"
        end
      end
    end
  end
end
