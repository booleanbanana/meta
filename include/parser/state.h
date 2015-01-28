/**
 * @file state.h
 * @author Chase Geigle
 *
 * All files in META are released under the MIT license. For more details,
 * consult the file LICENSE in the root of the project.
 */

#ifndef META_PARSER_STATE_H_
#define META_PARSER_STATE_H_

#include <memory>
#include <vector>

#include "parser/transition.h"
#include "parser/trees/node.h"
#include "parser/trees/parse_tree.h"
#include "sequence/sequence.h"
#include "util/persistent_stack.h"

namespace meta
{
namespace parser
{

class state
{
  public:
    using stack_type = util::persistent_stack<std::unique_ptr<node>>;

    state(const parse_tree& tree);
    state(const sequence::sequence& sentence);

    void advance(const transition& trans);

    /**
     * Checks if a transition is legal from a current state.
     *
     * @see http://www.aclweb.org/anthology/W09-3825 Appendix
     * @param trans The transition to check
     * @return whether that transition is legal
     */
    bool legal(const transition& trans) const;

    /**
     * Returns a transition used in situations where there is not a
     * transition in the model satisfying the constraints given in the
     * original paper so that the parser can at least make progress.
     */
    transition emergency_transition() const;

    const node* stack_item(size_t depth) const;
    const leaf_node* queue_item(ssize_t depth) const;

    size_t stack_size() const;
    size_t queue_size() const;

    bool finalized() const;

  private:
    stack_type stack_;
    std::vector<std::unique_ptr<leaf_node>> queue_;
    size_t q_idx_;
    bool done_;
};
}
}
#endif