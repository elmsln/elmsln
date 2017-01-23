import { Component, OnInit, Input } from '@angular/core';
import { Submission } from '../submission';
import { SubmissionService } from '../submission.service';

@Component({
  selector: 'app-submission-states',
  templateUrl: './submission-states.component.html',
  styleUrls: ['./submission-states.component.scss']
})
export class SubmissionStatesComponent implements OnInit {
  @Input() submission:Submission;
  states:any[];

  constructor(
    private submissionService:SubmissionService
  ) { }

  ngOnInit() {
    // get the list of states this submission could be
    let options = this.submissionService.getSubmissionOptions();
    options.state
      .map(state => {
        // check if this state is the active state of the submission
        // add an active property to the active state
        state['active'] = state.value === this.submission.state;

        // add custom inline styles if the item is active
        let styles = {};
        if (state.active) {
          styles = {
            'color': state.color,
            'background': state.color
          }
        }
        state['styles'] = styles;

        return state;
      })
    this.states = options.state;
  }
}
