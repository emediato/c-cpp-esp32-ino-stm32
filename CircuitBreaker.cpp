// https://martinfowler.com/bliki/Lambda.html

class CircuitBreaker:

  def call args
    case state
    when :closed
      begin
        do_call args
      rescue Timeout::Error
        record_failure
        raise $!
      end
    when :open then raise CircuitBreaker::Open
    else raise "Unreachable Code"
    end
  end
  def do_call args
    result = Timeout::timeout(@invocation_timeout) do
      @circuit.call args
    end
    reset
    return result
  end
  def record_failure
    @failure_count += 1
    @monitor.alert(:open_circuit) if :open == state
  end
  def reset
    @failure_count = 0
    @monitor.alert :reset_circuit
  end

/*
noun: a change made to the internal structure of software to make it easier to understand and cheaper to modify without changing its observable behavior

verb: to restructure software by applying a series of refactorings without changing its observable behavior.

Refactoring isn't another word for cleaning up code - it specifically defines one technique for improving the health of a code-base. I use "restructuring" as a more general term for reorganizing code that may incorporate other techniques.
*/
